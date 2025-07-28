/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** Game.hpp
*/

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/Parser/Parser.hpp"
#include "Renderer.hpp"
#include "NetworkManager.hpp"

class Game {
public:
    Game(NetworkManager& nm);
    void run(std::string ip, int port);
    NetworkManager& networkManager;

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    Renderer renderer;
    sf::View camera;
    sf::Clock clock;
};

#endif // GAME_HPP
