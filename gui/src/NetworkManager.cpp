/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** NetworkManager.cpp
*/

#include "NetworkManager.hpp"
#include <iostream>
#include <sstream>

NetworkManager::NetworkManager()
    : commands{ // Initialisation directe de l'unordered_map
        {
            "WELCOME", [this](std::istringstream& lineStream) {
                (void)lineStream;
                std::cout << "Received WELCOME message from server" << std::endl;
                sendCommand("GRAPHIC\n");
                sendCommand("msz\n");
            }
        },
        {
            "msz", [this](std::istringstream& lineStream) {
                int width, height;
                lineStream >> width >> height;
                mapWidth = width;
                mapHeight = height;
                std::cout << "Map size received: " << width << "x" << height << std::endl;
            }
        },
        {
            "bct", [this](std::istringstream& lineStream) {
                tiles_t tile;
                lineStream >> tile.x >> tile.y >> tile.resources[FOOD] >> tile.resources[LINEMATE] >> tile.resources[DERAUMERE] >> tile.resources[SIBUR] >> tile.resources[MENDIANE] >> tile.resources[PHIRAS] >> tile.resources[THYSTAME];
                tiles[std::to_string(tile.x) + ":" + std::to_string(tile.y)] = tile;
                //std::cout << "Tile received: " << tile.x << ", " << tile.y << " with resources: " << tile.resources[FOOD] << " " << tile.resources[LINEMATE] << " " << tile.resources[DERAUMERE] << " " << tile.resources[SIBUR] << " " << tile.resources[MENDIANE] << " " << tile.resources[PHIRAS] << " " << tile.resources[THYSTAME] << std::endl;
            }
        },
        {
            "tna", [this](std::istringstream& lineStream) {
                std::string teamName;
                lineStream >> teamName;
                std::cout << "Team name received: " << teamName << std::endl;
                teamNames.push_back(teamName);
            }
        },
        {
            "pnw", [this](std::istringstream& lineStream) {
                server_player_t player;
                lineStream >> player.id >> player.x >> player.y >> player.ori >> player.level >> player.teamName;
                player.orientation = static_cast<orientation_t>(player.ori);
                players[player.id] = player;
                std::cout << "New player connected: " << player.id << " at position " << player.x << ", " << player.y << " in team " << player.teamName << std::endl;
            }
        },
        {
            "ppo", [this](std::istringstream& lineStream) {
                int playerId;
                lineStream >> playerId;
                server_player_t player = players[playerId];
                lineStream >> player.x >> player.y >> player.ori;
                player.orientation = static_cast<orientation_t>(player.ori);
                players[playerId] = player;
                std::cout << "Player position updated: " << player.id << " at position " << player.x << ", " << player.y << std::endl;
            }
        },
        {
            "sgt", [this](std::istringstream& lineStream) {
                int timeUnit;
                lineStream >> timeUnit;
                std::cout << "Time unit received: " << timeUnit << std::endl;
            }
        },
        {
            "enw", [this](std::istringstream& lineStream) {
                int eggId, playerId, x, y;
                lineStream >> eggId >> playerId >> x >> y;
                std::cout << "New egg laid: " << eggId << " by player " << playerId << " at position " << x << ", " << y << std::endl;
            }
        },
        {
            "eht", [this](std::istringstream& lineStream) {
                int eggId;
                lineStream >> eggId;
                std::cout << "Egg hatched: " << eggId << std::endl;
            }
        },
        {
            "plv", [this](std::istringstream& lineStream) {
                int playerId, level;
                lineStream >> playerId >> level;
                players[playerId].level = level;
                std::cout << "Player level updated: " << playerId << " to level " << level << std::endl;
            }
        }
    }
{
    status = sf::Socket::NotReady;
    accumulatedMessage = "";
    mapWidth = 0;
    mapHeight = 0;
    received = 0;
    teamNames = {};
    players = {};
    tiles = {};
    is_connected = false;
}

void NetworkManager::connectToServer(const std::string& address, unsigned short port)
{
    if (socket.connect(address, port) == sf::Socket::Done) {
        status = sf::Socket::Done;
        std::cout << "Connected to server" << std::endl;
<<<<<<< HEAD
        //sendCommand("msz\n");
=======
        sendCommand("msz\n");
        is_connected = true;
>>>>>>> b6099775783153073e631e237cc26d96634eac17
    } else {
        std::cout << "Failed to connect to server" << std::endl;
        is_connected = false;
    }
}

void NetworkManager::sendCommand(const std::string& command)
{
    if (status == sf::Socket::Done) {
        socket.send(command.c_str(), command.size());
        std::cout << "Sent command to server: " << command << std::endl;
    }
}

void NetworkManager::update()
{
    if (status != sf::Socket::Done) {
        return;
    }

    if (socket.receive(data, sizeof(data), received) == sf::Socket::Done) {
        std::string message(data, received);
        handleMessage(message);
    }
}

void NetworkManager::handleMessage(const std::string& message)
{
    accumulatedMessage += message;
    size_t pos;
    while ((pos = accumulatedMessage.find('\n')) != std::string::npos) {
        std::string line = accumulatedMessage.substr(0, pos);
        accumulatedMessage.erase(0, pos + 1);
        std::istringstream lineStream(line);
<<<<<<< HEAD
        std::string command;
        lineStream >> command;

        if (command == "WELCOME") {
            std::cout << "Received WELCOME message from server" << std::endl;
            sendCommand("GRAPHIC\n");
            //sendCommand("msz\n");
        } else if (command == "msz") {
            int width, height;
            lineStream >> width >> height;
            mapWidth = width;
            mapHeight = height;
            std::cout << "Map size received: " << width << "x" << height << std::endl;
        } else if (command == "bct") {
            int x, y, q0, q1, q2, q3, q4, q5, q6;
            lineStream >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
            if (tileMap.find({x, y}) == tileMap.end()) {
                tileMap[{x, y}] = Tile(x, y);
=======
        std::string server_command;
        lineStream >> server_command;
        for (const auto& command : commands) {
            if (server_command == command.first) {
                command.second(lineStream);
                break;
>>>>>>> b6099775783153073e631e237cc26d96634eac17
            }
        }
    }
    is_updated = true;
}

const std::vector<std::string>& NetworkManager::getTeamNames() const
{
    return teamNames;
}

int NetworkManager::getMapWidth() const
{
    return mapWidth;
}

int NetworkManager::getMapHeight() const
{
    return mapHeight;
}

std::vector<server_player_t> NetworkManager::getPlayers()
{
    std::vector<server_player_t> playerVector;
    for (const auto& pair : players) {
        playerVector.push_back(pair.second);
    }
    return playerVector;
}

tiles_t NetworkManager::getTileAt(int x, int y)
{
    return tiles[std::to_string(x) + ":" + std::to_string(y)];
}

std::vector<server_player_t> NetworkManager::getPlayersAt(int x, int y)
{
    std::vector<server_player_t> playerVector;
    for (const auto& pair : players) {
        if (pair.second.x == x && pair.second.y == y) {
            playerVector.push_back(pair.second);
        }
    }
    return playerVector;
}

std::unordered_map<std::string, tiles_t> NetworkManager::getTiles()
{
    return tiles;
}

NetworkManager& NetworkManager::operator=(const NetworkManager& other)
{
    if (this == &other) {
        return *this;
    }
    status = other.status;
    accumulatedMessage = other.accumulatedMessage;
    mapWidth = other.mapWidth;
    mapHeight = other.mapHeight;
    received = other.received;
    teamNames = other.teamNames;
    players = other.players;
    tiles = other.tiles;
    return *this;
}
