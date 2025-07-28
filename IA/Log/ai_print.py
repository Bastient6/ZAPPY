# -----------------------------------------------------------------------------
# Title:     main.py
# Purpose:   main file for the project
# Author:    Corentin / Thomas
# Date:      30/05/2024
# -----------------------------------------------------------------------------

from ..IA import ai


def ai_print(ai):
    print(ai.__name__())
    return ai