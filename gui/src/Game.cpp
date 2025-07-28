/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include <iostream>

Game::Game(NetworkManager &nm) : networkManager(nm), renderer(networkManager, window)
{
    window.create(sf::VideoMode(1920, 1080), "Zappy");
    window.setFramerateLimit(60);
    camera.setSize(window.getSize().x / 2, window.getSize().y / 2);
    camera.setCenter(window.getSize().x / 2, window.getSize().y / 2);
    camera.zoom(1.5f);
}

void Game::run(std::string ip, int port)
{
    std::string info = "Connecting to server...";
    while (!networkManager.is_connected) {
        networkManager.connectToServer(ip, port);
        renderer.loadScreen(info);
    }
    networkManager.update();
    sf::Clock clock;
    info = "Waiting for server response...";
    while (clock.getElapsedTime().asMilliseconds() < 5000) {
        renderer.loadScreen(info);
        if (clock.getElapsedTime().asMilliseconds() > 1000) {
            info = "Loading map...";
        }
        if (clock.getElapsedTime().asMilliseconds() > 2000) {
            info = "Loading resources...";
        }
        if (clock.getElapsedTime().asMilliseconds() > 4000) {
            info = "Loading players...";
        }
        networkManager.update();
    }
    while (window.isOpen()) {
        processEvents();
        update();
        if (clock.getElapsedTime().asMilliseconds() > 10) {
            render();
            clock.restart();
        }
        if (renderer.getMapSize().x == 0 || renderer.getMapSize().y == 0) {
            networkManager.update();
            renderer.draw();
        }
    }
}

void Game::processEvents()
{
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Resized) {
            renderer.draw();
            camera.setSize(window.getSize().x / 2, window.getSize().y / 2);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            camera.move(0, -10);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            camera.move(0, 10);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            camera.move(-10, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            camera.move(10, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            camera.zoom(0.9f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            camera.zoom(1.1f);
        }
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
            renderer.setMousePosition(worldPos);
        }
    }
}

void Game::update()
{
    networkManager.update();
    renderer.setNetworkManager(networkManager);
    renderer.makeResource();
    renderer.makePlayer();
}

void Game::render()
{
    window.setView(camera);
    window.clear(sf::Color(39, 132, 182));
    renderer.makeRender();
    window.display();
}
