/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** Renderer.cpp
*/

#include "Renderer.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

bool Renderer::loadTexture(sf::Texture& texture, const std::string& filepath)
{
    if (!texture.loadFromFile(filepath)) {
        return false;
    }
    return true;
}

Renderer::Renderer(NetworkManager& networkManager, sf::RenderWindow& window)
    : window(window), networkManager(networkManager)
{
    currentWaterFrame = 0;
    map = {};
    players = {};
    textures = {};
    animationWaterClock.restart();
    map_size = sf::Vector2i(networkManager.getMapWidth(), networkManager.getMapHeight());
    mousePosition = sf::Vector2f(0, 0);

    std::vector<std::string> texturePaths = {
        "gui/assets/Background/Water1.png",
        "gui/assets/Background/Water2.png",
        "gui/assets/Background/Water3.png",
        "gui/assets/Background/Water4.png",
        "gui/assets/tiles/HillsB.png",
        "gui/assets/tiles/HillsBL.png",
        "gui/assets/tiles/HillsBR.png",
        "gui/assets/tiles/HillsL.png",
        "gui/assets/tiles/HillsR.png",
        "gui/assets/tiles/HillsT.png",
        "gui/assets/tiles/HillsTL.png",
        "gui/assets/tiles/HillsTR.png",
        "gui/assets/tiles/grass.png",
        "gui/assets/ressources/food.png",
        "gui/assets/ressources/linemate.png",
        "gui/assets/ressources/deraumere.png",
        "gui/assets/ressources/sibur.png",
        "gui/assets/ressources/mendiane.png",
        "gui/assets/ressources/phiras.png",
        "gui/assets/ressources/thystame.png",
        "gui/assets/player1/Idle11.png",
        "gui/assets/player1/Idle12.png",
        "gui/assets/player1/Idle21.png",
        "gui/assets/player1/Idle22.png",
        "gui/assets/player1/Idle31.png",
        "gui/assets/player1/Idle32.png",
        "gui/assets/player1/Idle41.png",
        "gui/assets/player1/Idle42.png"
    };

    for (const std::string& texturePath : texturePaths) {
        sf::Texture texture;
        if (!loadTexture(texture, texturePath)) {
            std::cerr << "Failed to load texture: " << texturePath << std::endl;
        }
        textures[texturePath] = texture;
    }
}

sf::Vector2f Renderer::getTilePosition(int x, int y)
{
    if (map.find(std::to_string(x) + ":" + std::to_string(y)) == map.end()) {
        std::cerr << "getTilePosition: Tile not found" << std::endl;
        return sf::Vector2f(0, 0);
    }
    return map[std::to_string(x) + ":" + std::to_string(y)].real_position;
}

std::pair<int, int> Renderer::getTileFromPosition(const sf::Vector2f &position)
{
    for (const auto& pair : map) {
        const map_s& tile = pair.second;
        if (position.x >= tile.real_position.x && position.x <= tile.real_position.x + tile.size.x &&
            position.y >= tile.real_position.y && position.y <= tile.real_position.y + tile.size.y) {
            return tile.position;
        }
    }
    std::cerr << "getTileFromPosition: Tile not found" << std::endl;
    return std::make_pair(-1, -1);
}

void Renderer::draw()
{
    std::cout << "Drawing" << std::endl;
    map_size.x = networkManager.getMapWidth();
    map_size.y = networkManager.getMapHeight();

    std::cout << "draw Map size: " << map_size.x << "x" << map_size.y << std::endl;

    makeIland(sf::Vector2f(window.getSize().x / 2 - (map_size.x * TILE_SIZE) / 2,
        window.getSize().y / 2 - (map_size.y + 1) * TILE_SIZE / 2));
}

void Renderer::drawWater(const sf::Vector2f& position, const sf::Vector2f& mapSize)
{
    (void) position;
    (void) mapSize;
    if (animationWaterClock.getElapsedTime().asMilliseconds() > 200) {
        currentWaterFrame = (currentWaterFrame + 1) % 4;
        animationWaterClock.restart();
    }
    std::string currentTextureFile = "gui/assets/Background/Water" + std::to_string(currentWaterFrame + 1) + ".png";

    if (textures.find(currentTextureFile) == textures.end()) {
        std::cerr << "Texture '" << currentTextureFile << "' not found!" << std::endl;
        return;
    }

    sf::Sprite sprite;
    sprite.setScale(.5f, .5f);
    sprite.setTexture(textures[currentTextureFile]);

    sf::Vector2u textureSize = textures[currentTextureFile].getSize();
    sf::Vector2u windowSize = window.getSize();

    for (unsigned int x = 0; x < windowSize.x; x += textureSize.x / 2) {
        for (unsigned int y = 0; y < windowSize.y; y += textureSize.y / 2) {
            sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
            window.draw(sprite);
        }
    }
}


void Renderer::makeIland(const sf::Vector2f &position)
{
    int y = 0;
    int x = 0;

    map["0:0"] = map_s{std::make_pair(0, 0), sf::Vector2f(position.x + (x * TILE_SIZE + x), position.y + (y * TILE_SIZE + y)), sf::Vector2f(TILE_SIZE, TILE_SIZE), {}, textures["gui/assets/tiles/HillsTL.png"], sf::Vector2f(4.0f, 4.0f), {0, 0, 0, 0, 0, 0, 0}, false};
    for (x = 1; x < map_size.x - 1; x++) {
        map[std::to_string(x) + ":0"] = map_s{std::make_pair(x, 0), sf::Vector2f(position.x + (x * TILE_SIZE + x), position.y + (y * TILE_SIZE + y)), sf::Vector2f(TILE_SIZE, TILE_SIZE), {}, textures["gui/assets/tiles/HillsT.png"], sf::Vector2f(4.0f, 4.0f), {0, 0, 0, 0, 0, 0, 0}, false};
    }
    map[std::to_string(x) + ":0"] = map_s{std::make_pair(x, 0), sf::Vector2f(position.x + (x * TILE_SIZE + x), position.y + (y * TILE_SIZE + y)), sf::Vector2f(TILE_SIZE, TILE_SIZE), {}, textures["gui/assets/tiles/HillsTR.png"], sf::Vector2f(4.0f, 4.0f), {0, 0, 0, 0, 0, 0, 0}, false};
    for (x = 0, y = 1; y < map_size.y; y++) {
        map["0:" + std::to_string(y)] = map_s{std::make_pair(0, y), sf::Vector2f(position.x + (x * TILE_SIZE + x), position.y + (y * TILE_SIZE + y)), sf::Vector2f(TILE_SIZE, TILE_SIZE), {}, textures["gui/assets/tiles/HillsL.png"], sf::Vector2f(4.0f, 4.0f), {0, 0, 0, 0, 0, 0, 0}, false};
        for (x = 1; x < map_size.x - 1; x++) {
            map[std::to_string(x) + ":" + std::to_string(y)] = map_s{std::make_pair(x, y), sf::Vector2f(position.x + (x * TILE_SIZE + x), position.y + (y * TILE_SIZE + y)), sf::Vector2f(TILE_SIZE, TILE_SIZE), {}, textures["gui/assets/tiles/grass.png"], sf::Vector2f(4.0f, 4.0f), {0, 0, 0, 0, 0, 0, 0}, false};
        }
        map[std::to_string(x) + ":" + std::to_string(y)] = map_s{std::make_pair(x, y), sf::Vector2f(position.x + (x * TILE_SIZE + x), position.y + (y * TILE_SIZE + y)), sf::Vector2f(TILE_SIZE, TILE_SIZE), {}, textures["gui/assets/tiles/HillsR.png"], sf::Vector2f(4.0f, 4.0f), {0, 0, 0, 0, 0, 0, 0}, false};
        x = 0;
    }
    map["0:" + std::to_string(y)] = map_s{std::make_pair(0, y), sf::Vector2f(position.x + (x * TILE_SIZE + x), position.y + (y * TILE_SIZE + y)), sf::Vector2f(TILE_SIZE, TILE_SIZE), {}, textures["gui/assets/tiles/HillsBL.png"], sf::Vector2f(4.0f + 0.08, 2.0f), {0, 0, 0, 0, 0, 0, 0}, false};
    for (x = 1; x < map_size.x - 1; x++) {
        map[std::to_string(x) + ":" + std::to_string(y)] = map_s{std::make_pair(x, y), sf::Vector2f(position.x + (x * TILE_SIZE + x), position.y + (y * TILE_SIZE + y)), sf::Vector2f(TILE_SIZE, TILE_SIZE), {}, textures["gui/assets/tiles/HillsB.png"], sf::Vector2f(4.0f + 0.08, 2.0f), {0, 0, 0, 0, 0, 0, 0}, false};
    }
    map[std::to_string(x) + ":" + std::to_string(y)] = map_s{std::make_pair(x, y), sf::Vector2f(position.x + (x * TILE_SIZE + x), position.y + (y * TILE_SIZE + y)), sf::Vector2f(TILE_SIZE, TILE_SIZE), {}, textures["gui/assets/tiles/HillsBR.png"], sf::Vector2f(4.0f + 0.08, 2.0f), {0, 0, 0, 0, 0, 0, 0}, false};
}

void Renderer::makePlayer()
{
    auto server_players = networkManager.getPlayers();
    for (const auto& server_player : server_players) {
        if (players.find(server_player.teamName + std::to_string(server_player.id)) == players.end()) {
            std::cerr << "makePlayer: Player not found" << std::endl;
            std::cerr << "Player id: " << server_player.id << std::endl;
            players[server_player.teamName + std::to_string(server_player.id)] = player_s{std::to_string(server_player.x) + ":" + std::to_string(server_player.y), server_player.orientation, sf::Vector2i(server_player.x, server_player.y), sf::Vector2f(3, 3), sf::Color::Black, textures["gui/assets/player1/Idle41.png"], sf::Sprite(), sf::Clock(), 0, 200, true, true};
            return;
        }
        std::cout << "Player found: " << server_player.id << " last position: " << players[server_player.teamName + std::to_string(server_player.id)].position.x << ":" << players[server_player.teamName + std::to_string(server_player.id)].position.y << std::endl;
        std::cout << "Player new position: " << server_player.x << ":" << server_player.y << std::endl;
        players[server_player.teamName + std::to_string(server_player.id)].position = sf::Vector2i(server_player.x, server_player.y);
        players[server_player.teamName + std::to_string(server_player.id)].orientation = server_player.orientation;
    }
}

void Renderer::drawRandomResourceInTile(const sf::Vector2i& position, std::string texturePath, int type, int resourceQuantity)
{
    int randomX = 3 + rand() % (TILE_SIZE - 21);
    int randomY = 3 + rand() % (TILE_SIZE - 21);
    std::string tile = std::to_string(position.x) + ":" + std::to_string(position.y);
    if (map.find(tile) == map.end()) {
        std::cerr << "drawRandomResourceInTile: Tile not found" << std::endl;
        return;
    }
    if (map[tile].currentRessource[type] == resourceQuantity) {
        return;
    }
    if (map[tile].currentRessource[type] > resourceQuantity) {
        while (map[tile].currentRessource[type] != resourceQuantity) {
            map[tile].ressources.pop_back();
            map[tile].currentRessource[type]--;
        }
        map[tile].ressources.pop_back();
        map[tile].currentRessource[type]--;
        return;
    }
    randomX = getTilePosition(position.x, position.y).x + randomX;
    randomY = getTilePosition(position.x, position.y).y + randomY;
    map[tile].ressources.push_back(ressource_s{std::to_string(position.x) + ":" + std::to_string(position.y), type, sf::Vector2f(randomX, randomY), sf::Vector2f(1, 1), textures[texturePath]});
    map[tile].currentRessource[type]++;
}

void Renderer::makeResource()
{
    std::unordered_map<std::string, tiles_t> tiles = networkManager.getTiles();
    for (const auto& pair : tiles) {
        tiles_t tile = pair.second;
        for (auto resource : tile.resources) {
            int resourceQuantity = resource.second;
            if (resourceQuantity <= 0)
                continue;
            switch (resource.first) {
                case FOOD:
                    drawRandomResourceInTile(sf::Vector2i(tile.x, tile.y), "gui/assets/ressources/food.png", FOOD, resourceQuantity);
                break;
                case LINEMATE:
                    drawRandomResourceInTile(sf::Vector2i(tile.x, tile.y), "gui/assets/ressources/linemate.png", LINEMATE, resourceQuantity);
                break;
                case DERAUMERE:
                    drawRandomResourceInTile(sf::Vector2i(tile.x, tile.y), "gui/assets/ressources/deraumere.png", DERAUMERE, resourceQuantity);
                    break;
                case SIBUR:
                    drawRandomResourceInTile(sf::Vector2i(tile.x, tile.y), "gui/assets/ressources/sibur.png", SIBUR, resourceQuantity);
                    break;
                case MENDIANE:
                    drawRandomResourceInTile(sf::Vector2i(tile.x, tile.y), "gui/assets/ressources/mendiane.png", MENDIANE, resourceQuantity);
                    break;
                case PHIRAS:
                    drawRandomResourceInTile(sf::Vector2i(tile.x, tile.y), "gui/assets/ressources/phiras.png", PHIRAS, resourceQuantity);
                    break;
                case THYSTAME:
                    drawRandomResourceInTile(sf::Vector2i(tile.x, tile.y), "gui/assets/ressources/thystame.png", THYSTAME, resourceQuantity);
                    break;
            }
        }
    }
}

void Renderer::drawText(const std::string& textString, unsigned int characterSize, const sf::Color& color, const sf::Vector2f& position) {
    sf::Font font;
    font.loadFromFile("gui/assets/fonts/Minecraft.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(characterSize);
    text.setFillColor(color);
    text.setPosition(position);

    window.draw(text);
}

static bool isPointInRect(const sf::Vector2f& point, const sf::Vector2f& rectPosition, const sf::Vector2f& rectSize)
{
    if (point.x >= rectPosition.x && point.x <= rectPosition.x + rectSize.x &&
        point.y >= rectPosition.y && point.y <= rectPosition.y + rectSize.y) {
        return true;
    }
    return false;
}

void Renderer::makeRender()
{
    sf::Sprite sprite;
    drawWater(sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x, window.getSize().y));
    for (auto tile : map) {
        if (isPointInRect(mousePosition, tile.second.real_position, sf::Vector2f(TILE_SIZE, TILE_SIZE))) {
            sprite.setColor(sf::Color(255, 0, 255, 200));
        } else {
            sprite.setColor(sf::Color(255, 255, 255, 255));
        }
        sprite.setPosition(tile.second.real_position);
        sprite.setTexture(tile.second.texture);
        sprite.setScale(tile.second.scale);
        window.draw(sprite);
        for (auto ressource : tile.second.ressources) {
            sprite.setScale(ressource.size);
            sprite.setTexture(ressource.texture);
            sprite.setPosition(ressource.position);
            window.draw(sprite);
        }
    }
    for (auto& pair : players) {
        auto& player = pair.second;
        std::cout << "Player Orientation: " << player.orientation << std::endl;
        if (player.isIdle) {
            auto elapsed = player.animationClock.getElapsedTime().asMilliseconds();
            if (elapsed > player.animationSpeed) {
                player.sprite.setTexture(textures["gui/assets/player1/Idle" + std::to_string(player.orientation) + std::to_string(player.currentFrame + 1) + ".png"]);
                player.currentFrame = player.currentFrame == 0 ? 1 : 0;
                player.animationClock.restart();
            }
        }
        sf::Vector2f playerPosition = getTilePosition(player.position.x, player.position.y);
        player.sprite.setPosition(sf::Vector2f(playerPosition.x + (5), playerPosition.y + 5));
        player.sprite.setScale(player.size);
        player.sprite.setColor(player.color);
        window.draw(player.sprite);
    }
}

void Renderer::setNetworkManager(NetworkManager& networkManager)
{
    this->networkManager = networkManager;
}

sf::Vector2i Renderer::getMapSize()
{
    return map_size;
}

void Renderer::setMousePosition(const sf::Vector2f& position)
{
    mousePosition = position;
}

void Renderer::loadScreen(std::string info)
{
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture background;
    if (!texture.loadFromFile("gui/assets/load/load.png")) {
        std::cerr << "Failed to load texture: " << "gui/assets/load/load.png" << std::endl;
    }
    if (!background.loadFromFile("gui/assets/load/background.png")) {
        std::cerr << "Failed to load texture: " << "gui/assets/load/background.png" << std::endl;
    }
    window.clear(sf::Color(39, 132, 182));
    if (animationWaterClock.getElapsedTime().asMilliseconds() > 200) {
        currentWaterFrame = (currentWaterFrame + 1) % 6;
        animationWaterClock.restart();
    }
    sprite.setTexture(background);
    window.draw(sprite);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(40 * currentWaterFrame, 0, 40, 18));
    sprite.setScale(5, 5);
    sprite.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2 - 50);
    window.draw(sprite);
    drawText("Loading...", 50, sf::Color::White, sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 + 50));
    drawText(info, 30, sf::Color::White, sf::Vector2f(window.getSize().x / 2 - info.size() * 6, window.getSize().y / 2 + 200));
    drawText("TRANTRONION", 100, sf::Color::White, sf::Vector2f(window.getSize().x / 2 - 350, 100));
    window.display();
}