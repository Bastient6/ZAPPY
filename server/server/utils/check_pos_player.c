/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** check_pos_player.c
*/

#include "../../include/server.h"

int check_pos_player_x(server_t *server, int x)
{
    if (x >= server->width)
        return x - (server->width - 1);
    else if (x < 0)
        return (server->width - 1) - x;
    else
        return x;
}

int check_pos_player_y(server_t *server, int y)
{
    if (y >= server->height)
        return y - (server->height - 1);
    else if (y < 0)
        return (server->height - 1) - y;
    else
        return y;
}
