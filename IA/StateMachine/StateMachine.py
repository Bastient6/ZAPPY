# -----------------------------------------------------------------------------
# Title:     ia.py
# Purpose:   ia class for the project
# Author:    Corentin / Thomas
# Date:      30/05/2024
# -----------------------------------------------------------------------------

from Socket.protocol import Protocol
from Socket.socket import Socket, SocketException
import asyncio
import queue

RESEARCH = 'RESEARCH'
STARVATION = 'STARVATION'
EVOLUTION = 'EVOLUTION'


class State(Protocol):
    def __init__(self, team):
        from StateMachine.StateList.Visit import VisitState
        super().__init__()
        self.stack = []
        self.protocol = Protocol()
        self.idleState = VisitState(self)
        self.is_to_group = False
        self.is_grouped = False
        self.last_message = None
        self.nb_arrived = 0
        self.team = team

    async def apply(self, socket: Socket):
        if len(self.stack) == 0:
            return
        print("stackapply", self.stack)
        if self.stack and self.stack[-1] is not None:
            await self.stack[-1].apply(socket)
        else:
            print("AI: State is empty")

    def push(self, state):
        self.stack.append(state)

    def pop(self):
        if len(self.stack) == 0:
            self.push(self.idleState)
            return
        return self.stack.pop()
