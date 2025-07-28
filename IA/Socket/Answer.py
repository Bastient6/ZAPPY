# -----------------------------------------------------------------------------
# Title:     main.py
# Purpose:   main file for the project
# Author:    Corentin / Thomas
# Date:      30/05/2024
# -----------------------------------------------------------------------------

from Socket.Answers.OkKo import answer_ko
from Socket.Answers.OkKo import answer_ok
from Socket.Answers.Dead import answer_dead
from Socket.Answers.Value import answer_value
from Socket.Answers.Evolution import answer_evolution
from StateMachine.StateMachine import State
from StateMachine.StateList.Group import GroupSubState

def process_answer(answer):
    print(answer)

array = [
    ("value", answer_value),
    ("dead", answer_dead),
]

def answer_handler(answer, state : State):
    for key, func in array:
        if key.startswith(answer):
            if func:
                print("Answer: " + answer + " -> " + key + " -> " + str(func()))
                return func()
            return None
    if "Elevation underway Current level:" in answer:
        answer_evolution(answer)
    if "group" in answer:
        print ("_______________________________start_message_______________________________")
        state.is_to_group = True
        state.last_message = answer
        print ("_______________________________end_message_______________________________")
    return answer
