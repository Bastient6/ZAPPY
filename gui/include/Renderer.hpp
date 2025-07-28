/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** Renderer.hpp
*/

#ifndef RENDERER_HPP
#define RENDERER_HPP

#define TILE_SIZE 64

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include "Utils.hpp"
#include "NetworkManager.hpp"

typedef struct player_t {
    std::string tile;
    orientation_t orientation;
    sf::Vector2i position;
    sf::Vector2f size;
    sf::Color color;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Clock animationClock;
    int currentFrame;
    int animationSpeed;
    bool isIdle;
    bool isHarvesting;
} player_s;

typedef struct ressource_t {
    std::string tile;
    int type;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Texture texture;
} ressource_s;

typedef struct map_t {
    std::pair<int, int> position;
    sf::Vector2f real_position;
    sf::Vector2f size;
    std::vector<ressource_s> ressources;
    sf::Texture texture;
    sf::Vector2f scale;
    std::vector<int> currentRessource;
    bool is_over;
} map_s;

class Renderer {
public:
    Renderer(NetworkManager& networkManager, sf::RenderWindow& window);

    bool loadTexture(sf::Texture& texture, const std::string& filepath);

    void loadScreen(std::string info = "");

    void draw();

    void makeRender();

    void drawWater(const sf::Vector2f& position, const sf::Vector2f& size);

    void drawText(const std::string& textString, unsigned int characterSize, const sf::Color& color, const sf::Vector2f& position);

    void makeIland(const sf::Vector2f& position);

    sf::Vector2i getMapSize();

    void makePlayer();

    void makeResource();

    sf::Vector2f getTilePosition(int x, int y);

    std::pair<int, int> getTileFromPosition(const sf::Vector2f& position);

    void drawRandomResourceInTile(const sf::Vector2i& position, std::string texturePath, int type, int resourceQuantity);

    void setNetworkManager(NetworkManager& networkManager);

    void setMousePosition(const sf::Vector2f& position);
private:
    std::map<std::string, map_s> map;
    std::map<std::string, player_s> players;
    sf::RenderWindow& window;
    NetworkManager& networkManager;
    std::unordered_map<std::string, sf::Texture> textures;
    sf::Clock animationWaterClock;
    int currentWaterFrame;
    sf::Texture treeTexture;
    sf::Vector2i map_size;
    sf::Vector2f mousePosition;
};

#endif // RENDERER_HPP