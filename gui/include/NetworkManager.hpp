/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** NetworkManager.hpp
*/

#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <SFML/Network.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include "Utils.hpp"

typedef enum orientation_e {
    NORTH,
    EAST,
    SOUTH,
    WEST
} orientation_t;

typedef enum resources_type_e {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} resources_type_t;

typedef struct tiles_t {
    int x;
    int y;
    std::unordered_map<resources_type_t, int> resources;
} tiles_t;

typedef struct server_player_t {
    int id;
    int x;
    int y;
    orientation_t orientation;
    int ori;
    int level;
    std::string teamName;
} server_player_t;

class NetworkManager {
public:
    NetworkManager();
    void connectToServer(const std::string& address, unsigned short port);
    void update();
    void sendCommand(const std::string& command);
    void handleMessage(const std::string& message);
    NetworkManager& operator=(const NetworkManager& other);
    tiles_t getTileAt(int x, int y);
    std::vector<server_player_t> getPlayersAt(int x, int y);
    std::unordered_map<std::string, tiles_t> getTiles();
    const std::vector<std::string>& getTeamNames() const;
    int getMapWidth() const;
    int getMapHeight() const;
    std::vector<server_player_t> getPlayers();
    bool is_updated;
    bool is_connected;

private:
    sf::TcpSocket socket;
    sf::Socket::Status status;
    char data[100]{};
    std::size_t received;
    std::unordered_map<std::string, tiles_t> tiles;
    std::string accumulatedMessage;
    std::vector<std::string> teamNames;
    std::map<int, server_player_t> players;
    std::unordered_map<std::string, std::function<void(std::istringstream&)>> commands;
    int mapWidth;
    int mapHeight;
};

#endif // NETWORKMANAGER_HPP
