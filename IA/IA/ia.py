# -----------------------------------------------------------------------------
# Title:     ia.py
# Purpose:   ia class for the project
# Author:    Corentin / Thomas
# Date:      30/05/2024
# -----------------------------------------------------------------------------
import os

from Socket.socket import Socket, SocketException
from Socket.protocol import Protocol
from StateMachine.StateMachine import State
from StateMachine.StateList.Visit import VisitState
import signal
from StateMachine.StateList.Search import SearchState, TakeFoodState
from StateMachine.StateList.SearchStone import SearchStoneState
from StateMachine.StateList.Fork import ForkState
from StateMachine.StateList.Group import GroupMasterState, GroupSubState
from Socket.Answer import answer_handler
from IA.Elevation import elevation_table
from enum import Enum
import asyncio
import re

class IA_TYPE(Enum):
    MASTER = 0
    SUB = 1

class IA(State, Protocol):
    def __init__(self, host, port, team, t):
        self.team = team
        super().__init__(team)
        self.socket = Socket(host, port)
        self.clientNumber = 0
        self.worldDimension = (0, 0)
        self.position = (0, 0)
        self.stateMachine = State(team)
        self.type = t
        self.nb_sub = 0
        self.pidList = []

    def __delete__(self, instance):
        self.socket.close()
        for pid in self.pidList:
            os.waitpid(pid, 0)

    async def connect(self):
        loop = asyncio.get_event_loop()
        for signame in {'SIGINT', 'SIGTERM'}:
            loop.add_signal_handler(getattr(signal, signame), self.socket._handle_sigint)
        await self.socket.connect()
        try:
            message = await self.socket.pop()
            if message != "WELCOME":
                raise SocketException("Connection failed", "Connection failed")
            await self.socket.send(self.team)  # Add 'await' here
            self.clientNumber = int(await self.socket.pop())
            world_dimension_str = await self.socket.pop()
            self.worldDimension = tuple(map(int, world_dimension_str.split(" ")))
            print("client " + self.clientNumber.__str__())
            print(self.worldDimension)
        except SocketException as e:
            print(e)
            self.socket.close()
            exit(1)

    async def run(self):
        await self.connect()
        while True:
            await self.socket.send(self.protocol.inventory())
            message = await self.socket.pop()
            print("inventory :")
            print(message)
            print('_______________________________reseponse_stack_______________________________')
            print(self.stateMachine.stack)
            print('_______________________________end_reseponse_stack_______________________________')
            await self.setTheNextState()
            await self.stateMachine.apply(self.socket)

    async def getInventory(self):
        await self.socket.send(self.protocol.inventory())
        inventory = answer_handler(await self.socket.pop(), self.stateMachine)
        pattern = r'^\[.*\]$'
        if not isinstance(inventory, str) and not re.match(pattern, inventory):
            return []
        items = inventory.strip('[]').split(',')
        items = [item.strip().split(' ') for item in items]
        return items

    async def setTheNextState(self):
        if self.stateMachine.stack:
            return
        if (self.type == IA_TYPE.SUB and self.stateMachine.is_to_group == True):
            print("AI: GroupSubState start start start start")
            self.stateMachine.push(GroupSubState(self.stateMachine, self.stateMachine.last_message))
            return
        await TakeFoodState(self.stateMachine).apply(self.socket)
        await self.socket.send(self.protocol.connect_nbr())
        message = answer_handler(await self.socket.pop(), self.stateMachine)
        items = await self.getInventory()
        if items != [] and len(items[0]) > 1 and items[0][1].isdigit() and int(items[0][1]) <= 15 or self.type == IA_TYPE.SUB:
            self.stateMachine.push(SearchState(self.stateMachine, Protocol.food))
            return
        
        if self.type == IA_TYPE.MASTER and self.getFoodinInventory(items) > 50 and self.isAllStone(items):
            self.stateMachine.push(GroupMasterState(self.stateMachine))
            return
        if self.type == IA_TYPE.MASTER and message.isdigit() and int(message) > 0 and self.nb_sub < 6:
            self.stateMachine.push(ForkState(self.stateMachine, self.fork, self))
            self.nb_sub += 1
            return
        if self.type == IA_TYPE.MASTER:
            self.stateMachine.push(SearchStoneState(self.stateMachine))

    def fork(self):
        ia = IA(self.socket.host, self.socket.port, self.team, IA_TYPE.SUB)
        asyncio.run(ia.run())

    def getFoodinInventory(self, inventory):
        for inv, quantity in inventory:
            if inv == "food":
                return int(quantity)
        return 0
    
    def isAllStone(self, inventory):
        for inv, quantity in inventory:
            if inv == "food":
                continue
            if inv == "linemate" and int(quantity) < elevation_table[8][inv]:
                return False
            if inv == "deraumere" and int(quantity) < elevation_table[8][inv]:
                return False
            if inv == "sibur" and int(quantity) < elevation_table[8][inv]:
                return False
            if inv == "mendiane" and int(quantity) < elevation_table[8][inv]:
                return False
            if inv == "phiras" and int(quantity) < elevation_table[8][inv]:
                return False
            if inv == "thystame" and int(quantity) < elevation_table[8][inv]:
                return False
        return True