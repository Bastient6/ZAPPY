# -----------------------------------------------------------------------------
# Title:     main.py
# Purpose:   main file for the project
# Author:    Corentin / Thomas
# Date:      30/05/2024
# -----------------------------------------------------------------------------

from Socket.socket import Socket
from Socket.protocol import Protocol

from IA.Elevation import elevation_table
import re
import asyncio
from time import sleep

class ElevationSubState(Protocol):
    def __init__(self, state):
        super().__init__()
        self.state = state

    async def apply(self, socket: Socket):
        print("AI: elevation")
        from Socket.Answer import answer_handler



class ElevationMasterState(Protocol):
    def __init__(self, state):
        super().__init__()
        self.state = state

    async def apply(self, socket: Socket):
        print("AI: elevation")
        from Socket.Answer import answer_handler
        for i in range(0, 9):
            await socket.send(self.state.protocol.set(self.state.protocol.linemate))
            message = answer_handler(await socket.pop(), self.state)
            print("linemate", message)
        for i in range(0, 9):
            await socket.send(self.state.protocol.set(self.state.protocol.deraumere))
            message = answer_handler(await socket.pop(), self.state)
            print("deraumere", message)
        for i in range(0, 10):
            await socket.send(self.state.protocol.set(self.state.protocol.sibur))
            message = answer_handler(await socket.pop(), self.state)
            print("sibur", message)
        for i in range(0, 5):
            await socket.send(self.state.protocol.set(self.state.protocol.mendiane))
            message = answer_handler(await socket.pop(), self.state)
            print("mendiane", message)
        for i in range(0, 6):
            await socket.send(self.state.protocol.set(self.state.protocol.phiras))
            message = answer_handler(await socket.pop(), self.state)
            print("phiras", message)
        for i in range(0, 1):
            await socket.send(self.state.protocol.set(self.state.protocol.thystame))
            message = answer_handler(await socket.pop(), self.state)
            print("thystame", message)
        for i in range(0, 8):
            await socket.send(self.state.protocol.incantation())
            message = answer_handler(await socket.pop(), self.state)
            print("incantation", message)
        #self.state.pop()
