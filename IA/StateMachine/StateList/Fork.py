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
import os

class ForkState(Protocol):
    def __init__(self, state, lambda_function=None, ia_instance=None):
        super().__init__()
        self.state = state
        self.lambda_function = lambda_function
        self.ia_instance = ia_instance

    async def apply(self, socket: Socket):
        print("AI: ForkState")
        await socket.send(self.state.protocol.fork())
        message = answer_handler(await socket.pop(), self.state)
        print ("_______________________________message fork_______________________________ !!!!!!!!!!!!!!!!!")
        print(message)
        if (message != "ok"):
            print("AI: ForkState: message != Ok")
            return
        self.state.pop()
        print(self.state.stack)
        newpid = os.fork()
        if newpid == 0:
            if self.lambda_function is not None:
                self.lambda_function()
            exit(0)
        else:
            print("AI: Forked")
            self.ia_instance.pidList.append(newpid)