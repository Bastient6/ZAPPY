/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** main.cpp
*/

#include <iostream>

#include "Game.hpp"
#include "NetworkManager.hpp"

int main(int argc, char* argv[])
{
    Parser parser(argc, argv);

    parser.parseArgs(argc, argv);

    NetworkManager networkManager;
    std::cout << "IP: " << parser.getIp() << std::endl;
    std::cout << "PORT: " << parser.getPort() << std::endl;
    Game game(networkManager);
    game.run(parser.getIp(), parser.getPort());

    return 0;
}
