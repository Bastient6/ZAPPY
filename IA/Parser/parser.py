# -----------------------------------------------------------------------------
# Title:     parser
# Purpose:   parser file for the project
# Author:    Corentin / Thomas
# Date:      30/05/2024
# -----------------------------------------------------------------------------
import argparse


class Parser:
    def __init__(self):
        self.port = 0
        self.name = ""
        self.machine = "localhost"
        self.parser = argparse.ArgumentParser(description='AI for Zappy.', add_help=False)

    def parse_args(self):
        self.parser.add_argument('-help', action='help', help='USAGE: ./zappy_gui -p port -h machine')
        self.parser.add_argument('-p', type=int, required=True, help='port')
        self.parser.add_argument('-n', type=str, required=True, help='team name')
        self.parser.add_argument('-h', '--host', type=str, required=True, help='machine address')

        args = self.parser.parse_args()

        self.port = self.verify_port(args.p)
        if self.port == -1:
            self.parser.print_help()
            exit(1)

        self.name = args.n
        self.machine = args.host
        return self.port, self.name, self.machine

    def verify_port(self, port):
        if port < 0 or port > 65535:
            print("Port must be between 0 and 65535")
            return -1
        return port
