/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Parser.cpp
*/

#include "../../include/Parser/Parser.hpp"
#include <iostream>
#include <string>

Parser::Parser(int ac, char **av)
{
    _port = 0;
    _ip = "";
    try {
        parseArgs(ac, av);
    } catch (Errors &e) {
        std::cerr << e.what() << std::endl;
        help();
        exit(84);
    }
}

void Parser::checkPort(const std::string &port)
{
    for (char i : port) {
        if (!std::isdigit(i))
            throw Errors("Invalid port");
    }
    _port = std::stoi(port);
}

void Parser::checkIp(const std::string &ip)
{
    for (char i : ip) {
        if (!std::isdigit(i) && i != '.')
            throw Errors("Invalid ip");
    }
    _ip = ip;
}

void Parser::parseArgs(int ac, char **av)
{
    if (ac != 5)
        throw Errors("Invalid number of arguments");
    for (int i = 1; i < ac; i++) {
        if (std::string(av[i]) == "-p") {
            checkPort(av[i + 1]);
        } else if (std::string(av[i]) == "-h") {
            checkIp(av[i + 1]);
        }
    }
}

void Parser::help()
{
    std::cout << "USAGE: ./zappy_gui -p port -h machine\n";
}
