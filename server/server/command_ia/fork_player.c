/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** fork_player.c
*/

#include "./include/command_ia.h"

int fork_player(char *command, server_t *server, client_t *client)
{
    (void) server;
    (void) command;
    return dprintf(client->fd, "ok\n");
}
