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
from StateMachine.StateList.Search import SearchState
from Socket.Answer import answer_handler
from IA.Elevation import elevation_table
import re

class SearchStoneState(Protocol):
    def __init__(self, state):
        super().__init__()
        self.state = state
    def check_unpack(self, inventory):
        return all(len(item) >= 2 for item in inventory)

    async def apply(self, socket: Socket):
        print("AI: SearchStoneState")
        is_moved = False
        self.state.pop()
        print(self.state.stack)
        await socket.send(self.state.protocol.look())
        message = answer_handler(await socket.pop(), self.state)
        pattern = r'^\[.*\]$'
        if not isinstance(message, str) and not re.match(pattern, message):
            return
        items = message.strip('[]').split(',')
        items = [item.strip().split(' ') for item in items]
        inventory = await self.getInventory(socket)
        if inventory == [] or items == []:
            self.state.push(VisitState(self.state))
            return
        print("AI: Found " + str(items) + " items  ")
        print ("ai inventory search stone" + str(inventory))
        if (not self.check_unpack(inventory)):
            self.state.push(VisitState(self.state))
            return
        for inv, quantity in inventory:
            for itemPos in items:
                if inv == "food":
                    continue
                if inv in itemPos and quantity.isdigit() and int(quantity) < elevation_table[8][inv]:
                    print("AI: Found " + inv + "<-------------------------------" + str(itemPos.count(inv)) + " times")
                    is_moved = True
                    for nb in range(0, itemPos.count(inv)):
                        await SearchState(self.state, inv).apply(socket)
        print ("inventory :")
        print (inventory)
        print("AI: Researching for stone in ")
        print(items)
        if (is_moved == False):
            self.state.push(VisitState(self.state))
        return

    async def getInventory(self, socket):
        await socket.send(self.state.protocol.inventory())
        inventory = answer_handler(await socket.pop(), self.state)
        pattern = r'^\[.*\]$'
        if not isinstance(inventory, str) and not re.match(pattern, inventory):
            return []
        items = inventory.strip('[]').split(',')
        items = [item.strip().split(' ') for item in items]
        return items