# -----------------------------------------------------------------------------
# Title:     main.py
# Purpose:   main file for the project
# Author:    Corentin / Thomas
# Date:      30/05/2024
# -----------------------------------------------------------------------------

import Parser.parser as parser
from Socket.socket import SocketException
from IA.ia import IA, IA_TYPE
import asyncio

def main():
    p = parser.Parser()
    p.parse_args()
    print("Port: " + str(p.port))
    ia = IA(p.machine, p.port, p.name, IA_TYPE.MASTER)
    try:
        asyncio.run(ia.run())
    except SocketException as e:
        print(e)
        exit(1)
    ia.show()

if __name__ == "__main__":
    main()
