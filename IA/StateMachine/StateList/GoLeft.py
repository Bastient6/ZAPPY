# -----------------------------------------------------------------------------
# Title:     main.py
# Purpose:   main file for the project
# Author:    Corentin / Thomas
# Date:      30/05/2024
# -----------------------------------------------------------------------------

from Socket.socket import Socket


class GoLeftState:
    def __init__(self, state):
        self.state = state

    async def apply(self, socket: Socket):
        from Socket.Answer import answer_handler
        await socket.send(self.state.protocol.left())
        message = answer_handler(await socket.pop(), self.state)
        if message == False:
            print("AI: Can't go left")
            return
        print("AI: Going left")
        self.state.pop()
