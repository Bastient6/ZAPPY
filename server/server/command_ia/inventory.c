/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** inventory.c
*/

#include "./include/command_ia.h"

int inventoy_player(char *command, server_t *server, client_t *client)
{
    (void) server;
    (void) command;
    return dprintf(client->fd, "[food %d, linemate %d, deraumere %d, sibur %d,"
    " mendiane %d, phiras %d, thystame %d]\n",
    client->inventory->food,
    client->inventory->linemate, client->inventory->deraumere,
    client->inventory->sibur, client->inventory->mendiane,
    client->inventory->phiras, client->inventory->thystame);
}
