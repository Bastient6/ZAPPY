# -----------------------------------------------------------------------------
# Title:     main.py
# Purpose:   main file for the project
# Author:    Corentin / Thomas
# Date:      30/05/2024
# -----------------------------------------------------------------------------

from Socket.socket import Socket
from Socket.protocol import Protocol

from StateMachine.StateList.GoForward import GoForwardState
from StateMachine.StateList.GoLeft import GoLeftState
from StateMachine.StateList.GoRight import GoRightState
from StateMachine.StateList.Visit import VisitState
import re


class SearchState(Protocol):
    def __init__(self, state, obj):
        super().__init__()
        self.state = state
        self.object = obj

    async def apply(self, socket: Socket):
        from Socket.Answer import answer_handler
        print("AI: SearchState for : " + self.object)
        await socket.send(self.state.protocol.look())
        message = answer_handler(await socket.pop(), self.state)
        pattern = r'^\[.*\]$'
        if not isinstance(message, str) and not re.match(pattern, message):
            return
        items = message.strip('[]').split(',')
        items = [item.strip() for item in items]
        if items[0].find(self.object) != -1:
            await socket.send(self.state.protocol.take(self.object))
            message = answer_handler(await socket.pop(), self.state)
            if message == 1:
                print("AI: Took " + self.object)
            self.state.pop()
            return
        pos = self.get_index(items, self.object)
        if pos != -1:
            print("AI: Move to " + self.object)
            self.move_to_index(items, pos)
            return
        print("AI: No" + self.object + " found")
        self.state.pop()
        self.state.push(VisitState(self.state))
        return

    def get_index(self, items, item):
        for i in range(len(items)):
            if items[i].find(item) != -1:
                return i
        return -1

    def move_to_index(self, items, index):
        items.pop(0)
        for i in range(1, items.__len__() + 1):
            for j in range(1 + 2 * (i - 1), (1 + 2 * i)):
                if j == index:
                    for k in range(i):
                        self.state.push(GoForwardState(self.state))
                    if j < (1 + 2 * i) - (1 + 2 * (i - 1)):
                        self.state.push(GoLeftState(self.state))
                    elif j > (1 + 2 * i) - (1 + 2 * (i - 1)):
                        self.state.push(GoRightState(self.state))
                    for k in range(((1 + 2 * i) - (1 + 2 * (i - 1) / 2)).__floor__() - 1):
                        self.state.push(GoForwardState(self.state))
                    return

class TakeFoodState(Protocol):
    def __init__(self, state):
        super().__init__()
        self.state = state

    async def apply(self, socket: Socket):
        from Socket.Answer import answer_handler
        await socket.send(self.state.protocol.look())
        message = answer_handler(await socket.pop(), self.state)
        pattern = r'^\[.*\]$'
        if not isinstance(message, str) and not re.match(pattern, message):
            return
        items = message.strip('[]').split(',')
        items = [item.strip() for item in items]
        print ("take food : items = ", items)
        for i in range(0, items[0].count("food")):
            await socket.send(self.state.protocol.take("food"))
            message = answer_handler(await socket.pop(), self.state)
            if message == 1:
                print("AI: Took food")
        #self.state.pop()
        return
