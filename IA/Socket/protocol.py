# -----------------------------------------------------------------------------
# Title:     main.py
# Purpose:   main file for the project
# Author:    Corentin / Thomas
# Date:      30/05/2024
# -----------------------------------------------------------------------------

SEPARATOR_SUFFIX = " "


class Protocol:
    def __init__(self):
        self.END_SUFFIX = '\n'
        self.SEPARATOR_SUFFIX = " "

    def forward(self):
        return "Forward"

    def right(self):
        return "Right"

    def left(self):
        return "Left"

    def look(self):
        return "Look"

    def inventory(self):
        return "Inventory"

    def broadcast(self,team, message):
        return "Broadcast" + self.SEPARATOR_SUFFIX + team + "_" + message

    def connect_nbr(self):
        return "Connect_nbr"

    def fork(self):
        return "Fork"

    def eject(self):
        return "Eject"

    def take(self, resource):
        return "Take" + self.SEPARATOR_SUFFIX + resource

    def set(self, resource):
        return "Set" + self.SEPARATOR_SUFFIX + resource

    def incantation(self):
        return "Incantation"

    food = "food"
    linemate = "linemate"
    deraumere = "deraumere"
    sibur = "sibur"
    mendiane = "mendiane"
    phiras = "phiras"
    thystame = "thystame"
