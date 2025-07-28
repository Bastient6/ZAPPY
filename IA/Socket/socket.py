# -----------------------------------------------------------------------------
# Title:     ia.py
# Purpose:   ia class for the project
# Author:    Corentin / Thomas
# Date:      30/05/2024
# -----------------------------------------------------------------------------

import asyncio

END_SUFFIX = '\n'
SEPARATOR_SUFFIX = ":"


class Socket:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.reader = None
        self.writer = None
        self.messageQueue = asyncio.Queue(100)
        self.receive_task = None
        self.message_received = asyncio.Event()
        self.queue_lock = asyncio.Lock()
        self.stop_event = asyncio.Event()

    async def connect(self):
        self.reader, self.writer = await asyncio.open_connection(self.host, self.port)
        self.start_receive()

    def start_receive(self):
        self.receive_task = asyncio.create_task(self.receive())

    async def send(self, message):
        self.writer.write((message + '\n').encode())
        await self.writer.drain()

    async def receive(self):
        while not self.stop_event.is_set():
            try:
                data = await self.reader.readline()
                if not data:
                    continue
                data = data.decode().strip()
                await self.messageQueue.put(data)
                self.message_received.set()
            except asyncio.CancelledError:
                print("Receive task was cancelled.")
                break
            except Exception as e:
                print(f"An unexpected error occurred: {e}")

    async def stop(self):
        self.stop_event.set()
        print("Stopping the IA...")
        exit(84)

    def _handle_sigint(self):
        asyncio.get_event_loop().create_task(self.stop())

    def close(self):
        self.writer.close()
        asyncio.run(self.writer.wait_closed())

    async def pop(self):
        try:
            await asyncio.wait_for(self.queue_lock.acquire(), timeout=1.0)
            message = await self.messageQueue.get()
            return message
        except asyncio.TimeoutError:
            print("Timeout while waiting for messageQueue")
            return None
        finally:
            if self.queue_lock.locked():
                self.queue_lock.release()


class SocketException(Exception):
    def __init__(self, message, errors):
        super().__init__(message)
        self.errors = errors
