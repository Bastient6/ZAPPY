/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** command_content_of_a_tile
*/

#include "./include/command_gui.h"

int command_content_of_a_tile
(char *command, server_t *server, client_t *client)
{
    char **args = str_to_word_array(command, ' ');
    int x = atoi(args[1]);
    int y = atoi(args[2]);

    return dprintf(client->fd, "bct %d %d %d %d %d %d %d %d %d\n"
    , x, y, server->content[y][x].linemate,
        server->content[y][x].deraumere,
        server->content[y][x].sibur, server->content[y][x].mendiane,
        server->content[y][x].phiras,
        server->content[y][x].thystame, server->content[y][x].food);
}
