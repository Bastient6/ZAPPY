/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** look.c
*/
#include "./include/command_ia.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *my_strcat(char *dest, const char *new)
{
    size_t len_dest = strlen(dest);
    size_t len_new = strlen(new);
    char *ret = malloc(len_dest + len_new + 1);

    if (!ret)
        return NULL;
    strcat(ret, dest);
    strcat(ret, new);
    return ret;
}

char *see(server_t *server, int x, int y)
{
    char *ret = malloc(sizeof(char) * 1);

    if (server->content[y][x].nb_playeur > 0)
        ret = my_strcat(ret, " player");
    if (server->content[y][x].deraumere > 0)
        ret = my_strcat(ret, " deraumere");
    if (server->content[y][x].food > 0)
        ret = my_strcat(ret, " food");
    if (server->content[y][x].linemate > 0)
        ret = my_strcat(ret, " linemate");
    if (server->content[y][x].mendiane > 0)
        ret = my_strcat(ret, " mendiane");
    if (server->content[y][x].phiras > 0)
        ret = my_strcat(ret, " phiras");
    if (server->content[y][x].sibur > 0)
        ret = my_strcat(ret, " sibur");
    if (server->content[y][x].thystame > 0)
        ret = my_strcat(ret, " thystame");
    return ret;
}

char *were_see(server_t *server, int x, int y, client_t *client)
{
    switch (client->orientation) {
        case 1:
            return see(server, check_pos_player_x(server, client->pos_x + x),
            check_pos_player_y(server, client->pos_y - y));
        case 2:
            return see(server, check_pos_player_x(server, client->pos_x + y),
            check_pos_player_y(server, client->pos_y - x));
        case 3:
            return see(server, check_pos_player_x(server, client->pos_x - x),
            check_pos_player_y(server, client->pos_y + y));
        case 4:
            return see(server, check_pos_player_x(server, client->pos_x - y),
            check_pos_player_y(server, client->pos_y + x));
        default:
            return NULL;
    }
}

int look(char *command, server_t *server, client_t *client)
{
    char *ret = malloc(sizeof(char) * 3);
    int result;

    (void) command;
    ret = my_strcat(ret, "[ ");
    for (int y = 0; y <= client->level; y++)
        for (int x = -y; x <= y; x++) {
            ret = my_strcat(ret, were_see(server, x, y, client));
            ret = my_strcat(ret, ",");
        }
    if (ret[strlen(ret) - 1] == ',') {
        ret[strlen(ret) - 1] = ' ';
        ret = my_strcat(ret, "]");
    } else
        ret = my_strcat(ret, " ]");
    result = dprintf(client->fd, "%s\n", ret);
    free(ret);
    return result;
}
