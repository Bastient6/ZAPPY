# -----------------------------------------------------------------------------
# Title:     main.py
# Purpose:   main file for the project
# Author:    Corentin / Thomas
# Date:      30/05/2024
# -----------------------------------------------------------------------------

from Socket.socket import Socket
import random


class VisitState:
    def __init__(self, state):
        self.state = state

    async def apply(self, socket: Socket):
        from Socket.Answer import answer_handler
        rand = random.randint(0, 5)
        print("_______________________________visit_________________________________")
        match rand:
            case 0:
                await socket.send(self.state.protocol.right())
                message = answer_handler(await socket.pop(), self.state)
                if message == False:
                    print("AI: Can't go right")
                    return
                await socket.send(self.state.protocol.forward())
                message = answer_handler(await socket.pop(), self.state)
                if message == False:
                    print("AI: Can't go right")
                    return
                print("AI: Going right")
            case 1:
                await socket.send(self.state.protocol.left())
                message = answer_handler(await socket.pop(), self.state)
                if message == False:
                    print("AI: Can't go right")
                    return
                await socket.send(self.state.protocol.forward())
                message = answer_handler(await socket.pop(), self.state)
                if message == False:
                    print("AI: Can't go left")
                    return
                print("AI: Going left")
            case _:
                await socket.send(self.state.protocol.forward())
                message = answer_handler(await socket.pop(), self.state)
                if message == False:
                    print("AI: Can't go forward")
                    return
                print("AI: Going forward")
        self.state.pop()
