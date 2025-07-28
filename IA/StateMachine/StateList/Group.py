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
from StateMachine.StateList.Elevation import ElevationSubState, ElevationMasterState
from IA.Elevation import elevation_table
import re
import asyncio
from time import sleep

class GroupMasterState(Protocol):
    def __init__(self, state):
        super().__init__()
        self.state = state

    async def apply(self, socket: Socket):
        print("AI: GroupMasterState")
        await socket.send(self.state.protocol.broadcast(self.state.team, "group"))
        from Socket.Answer import answer_handler
        print("message queue size : " + str(socket.messageQueue.qsize()))
        while socket.messageQueue.qsize() != 0:
            message = answer_handler(await socket.pop(), self.state)
            if "arrived" in message and self.state.team in message:
                print("AI: GroupMasterState: group" + str(self.state.nb_arrived))
                self.state.nb_arrived += 1
            if self.state.nb_arrived >= 5:
               self.state.pop()
               self.state.push(ElevationMasterState(self.state))

        sleep(1)


class GroupSubState(Protocol):
    def __init__(self, state, message):
        super().__init__()
        self.state = state
        self.message = message
    
    async def apply(self, socket: Socket):
        print("self.state " + str(self.state) + " self.message " + str(self.message))
        print("AI: GroupSubState")
        from Socket.Answer import answer_handler
        message = answer_handler(await socket.pop(), self.state)
        if "group" in message and self.state.team in message:
            self.message = message
        else :
            return
        print("AI: GroupSubState message : " + message)
        #self.state.pop()
        print("AI: GroupSubState message : " + self.message)
        self.state.is_to_group = True
        direction = extract_numbers(self.message)
        print("AI: GroupSubState direction : " + str(direction))
        if (self.state.is_grouped == True):
            self.state.pop()
            await socket.send(self.state.protocol.broadcast(self.state.team, "arrived"))
            message = answer_handler(await socket.pop(), self.state)
            self.state.push(ElevationSubState(self.state))
            print("AI: GroupSubState: arrived" + message)
            return
        match direction:
            case 1:
                self.state.push(GoForwardState(self.state))
            case 2:
                self.state.push(GoLeftState(self.state))
                self.state.push(GoForwardState(self.state))
            case 3:
                self.state.push(GoLeftState(self.state))
            case 4:
                self.state.push(GoForwardState(self.state))
                self.state.push(GoRightState(self.state))
                self.state.push(GoForwardState(self.state))
                self.state.push(GoLeftState(self.state))
                self.state.push(GoLeftState(self.state))
            case 5:
                self.state.push(GoLeftState(self.state))
                self.state.push(GoLeftState(self.state))
            case 6:
                self.state.push(GoLeftState(self.state))
                self.state.push(GoForwardState(self.state))
                self.state.push(GoRightState(self.state))
                self.state.push(GoRightState(self.state))
            case 7:
                self.state.push(GoRightState(self.state))
            case 8:
                self.state.push(GoRightState(self.state))
                self.state.push(GoForwardState(self.state)) 
            case _:
                self.state.is_grouped = True
        
    
def extract_numbers(s):
    tab = [int(match) for match in re.findall(r'\d+', s)]
    return int(tab[0])