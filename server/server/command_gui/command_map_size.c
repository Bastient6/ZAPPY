/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** command_map_size
*/

#include "./include/command_gui.h"

int command_map_size(char *command, server_t *server, client_t *client)
{
    (void)command;
    return dprintf(client->fd, "msz %d %d\n", server->width, server->height);
}
