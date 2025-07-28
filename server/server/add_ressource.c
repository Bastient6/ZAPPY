/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** add_ressource
*/

#include "../include/server.h"

int *actualy_ressource(server_t *server)
{
    int *ressource = malloc(sizeof(int) * 7);

    for (int i = 0; i < 7; i++)
        ressource[i] = 0;
    for (int y = 0; y < server->height; y++) {
        for (int x = 0; x < server->width; x++) {
            ressource[0] += server->content[y][x].food;
            ressource[1] += server->content[y][x].linemate;
            ressource[2] += server->content[y][x].deraumere;
            ressource[3] += server->content[y][x].sibur;
            ressource[4] += server->content[y][x].mendiane;
            ressource[5] += server->content[y][x].phiras;
            ressource[6] += server->content[y][x].thystame;
        }
    }
    return ressource;
}


void add_food_linemate(server_t *server, int food, int linemate)
{
    int x = 0;
    int y = 0;

    for (int i = 0; i < food; i++) {
        x = rand() % server->width;
        y = rand() % server->height;
        server->content[y][x].food += 1;
    }
    for (int i = 0; i < linemate; i++) {
        x = rand() % server->width;
        y = rand() % server->height;
        server->content[y][x].linemate += 1;
    }
}

void add_deraumere_sibur(server_t *server, int deraumere, int sibur)
{
    int x = 0;
    int y = 0;

    for (int i = 0; i < deraumere; i++) {
        x = rand() % server->width;
        y = rand() % server->height;
        server->content[y][x].deraumere += 1;
    }
    for (int i = 0; i < sibur; i++) {
        x = rand() % server->width;
        y = rand() % server->height;
        server->content[y][x].sibur += 1;
    }
}

void add_merndiane_phiras_thystame
(server_t *server, int mendiane, int phiras, int thystame)
{
    int x = 0;
    int y = 0;

    for (int i = 0; i < mendiane; i++) {
        x = rand() % server->width;
        y = rand() % server->height;
        server->content[y][x].mendiane += 1;
    }
    for (int i = 0; i < phiras; i++) {
        x = rand() % server->width;
        y = rand() % server->height;
        server->content[y][x].phiras += 1;
    }
    for (int i = 0; i < thystame; i++) {
        x = rand() % server->width;
        y = rand() % server->height;
        server->content[y][x].thystame += 1;
    }
}

void add_ressource(server_t *server)
{
    int *ressource = actualy_ressource(server);
    int food = FOOD * server->width * server->height - ressource[0];
    int linemate = LINEMATE * server->width * server->height - ressource[1];
    int deraumere = DERAUMERE * server->width * server->height - ressource[2];
    int sibur = SIBUR * server->width * server->height - ressource[3];
    int mendiane = MENDIANE * server->width * server->height - ressource[4];
    int phiras = PHIRAS * server->width * server->height - ressource[5];
    int thystame = THYSTAME * server->width * server->height - ressource[6];

    add_food_linemate(server, food, linemate);
    add_deraumere_sibur(server, deraumere, sibur);
    add_merndiane_phiras_thystame(server, mendiane, phiras, thystame);
}
