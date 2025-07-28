/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** init_server
*/

#include "../include/server.h"

void init_socket(server_t *server)
{
    int opt = 1;

    server->sockaddr_in.sin_family = AF_INET;
    server->sockaddr_in.sin_port = htons(server->port);
    server->sockaddr_in.sin_addr.s_addr = INADDR_ANY;
    if (setsockopt(server->fd, SOL_SOCKET,
    SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(84);
    }
}

void init_content(server_t *server)
{
    server->content = malloc(sizeof(content_t *) * server->height);
    for (int i = 0; i < server->height; i++) {
        server->content[i] = malloc(sizeof(content_t) * server->width);
    }
    for (int i = 0; i < server->height; i++) {
        for (int j = 0; j < server->width; j++) {
            server->content[i][j].deraumere = 0;
            server->content[i][j].linemate = 0;
            server->content[i][j].mendiane = 0;
            server->content[i][j].phiras = 0;
            server->content[i][j].sibur = 0;
            server->content[i][j].thystame = 0;
            server->content[i][j].food = 0;
        }
    }
}

void init_egg(server_t *server)
{
    team_t *team = server->teams;

    server->egg = malloc(sizeof(egg_t));
    server->egg = NULL;
    while (team != NULL) {
        for (int i = 0; i < team->maxClients; i++)
            server->egg = append_egg(server->egg, team->id, server);
        team = team->next;
    }
}

void init_server(server_t *server)
{
    server->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    init_socket(server);
    init_content(server);
    init_egg(server);
    server->clients = malloc(sizeof(client_t));
    server->clients = NULL;
    server->last_id = 1;
    server->time = 20 / server->freq;
}
