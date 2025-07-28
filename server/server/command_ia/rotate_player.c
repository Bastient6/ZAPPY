/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** rotate_player.c
*/

#include "./include/command_ia.h"

int rotate_playeur_right(char *command, server_t *server, client_t *client)
{
    (void) server;
    (void) command;
    client->orientation += 1;
    if (client->orientation < 1)
        client->orientation = 3;
    if (client->orientation > 3)
        client->orientation = 1;
    return dprintf(client->fd, "ok\n");
}

int rotate_playeur_left(char *command, server_t *server, client_t *client)
{
    (void) server;
    (void) command;
    client->orientation -= 1;
    if (client->orientation < 1)
        client->orientation = 3;
    if (client->orientation > 3)
        client->orientation = 1;
    return dprintf(client->fd, "ok\n");
}
