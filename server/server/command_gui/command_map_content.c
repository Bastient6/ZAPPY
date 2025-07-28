/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** command_map_content
*/

#include "./include/command_gui.h"

int command_map_content(char *command, server_t *server, client_t *client)
{
    (void)command;
    for (int i = 0; i < server->height; i++) {
        for (int j = 0; j < server->width; j++) {
            dprintf(client->fd, "bct %d %d %d %d %d %d %d %d %d\n", j, i,
            server->content[i][j].food,
            server->content[i][j].linemate,
            server->content[i][j].deraumere,
            server->content[i][j].sibur,
            server->content[i][j].mendiane,
            server->content[i][j].phiras,
            server->content[i][j].thystame);
        }
    }
    return 0;
}
