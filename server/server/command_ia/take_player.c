/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** take_player.c
*/

#include "./include/command_ia.h"

int take_player_end(server_t *server, client_t *client, char **args)
{
    if (strcmp(args[1], "thystame")) {
        if (server->content[client->pos_y][client->pos_x].thystame > 0) {
            server->content[client->pos_y][client->pos_x].thystame -= 1;
            client->inventory->thystame += 1;
            return dprintf(client->fd, "ok\n");
        } else
            return dprintf(client->fd, "ko\n");
    } else
        return dprintf(client->fd, "ko\n");
}

int take_player_next_bis(server_t *server, client_t *client, char **args)
{
    if (strcmp(args[1], "mendiane")) {
        if (server->content[client->pos_y][client->pos_x].mendiane > 0) {
            server->content[client->pos_y][client->pos_x].mendiane -= 1;
            client->inventory->mendiane += 1;
            return dprintf(client->fd, "ok\n");
        } else
            return dprintf(client->fd, "ko\n");
    }
    if (strcmp(args[1], "phiras")) {
        if (server->content[client->pos_y][client->pos_x].phiras > 0) {
            server->content[client->pos_y][client->pos_x].phiras -= 1;
            client->inventory->phiras += 1;
            return dprintf(client->fd, "ok\n");
        } else
            return dprintf(client->fd, "ko\n");
    } else
        return take_player_end(server, client, args);
}

int take_player_next(server_t *server, client_t *client, char **args)
{
    if (strcmp(args[1], "deraumere")) {
        if (server->content[client->pos_y][client->pos_x].deraumere > 0) {
            server->content[client->pos_y][client->pos_x].deraumere -= 1;
            client->inventory->deraumere += 1;
            return dprintf(client->fd, "ok\n");
        } else
            return dprintf(client->fd, "ko\n");
    }
    if (strcmp(args[1], "sibur")) {
        if (server->content[client->pos_y][client->pos_x].sibur > 0) {
            server->content[client->pos_y][client->pos_x].sibur -= 1;
            client->inventory->sibur += 1;
            return dprintf(client->fd, "ok\n");
        } else
            return dprintf(client->fd, "ko\n");
    } else
        return take_player_next_bis(server, client, args);
}

int take_playeur(char *command, server_t *server, client_t *client)
{
    char **args = str_to_word_array(command, ' ');

    if (strcmp(args[1], "food")) {
        if (server->content[client->pos_y][client->pos_x].food > 0) {
            server->content[client->pos_y][client->pos_x].food -= 1;
            client->inventory->food += 1;
            return dprintf(client->fd, "ok\n");
        } else
            return dprintf(client->fd, "ko\n");
    }
    if (strcmp(args[1], "linemate")) {
        if (server->content[client->pos_y][client->pos_x].linemate > 0) {
            server->content[client->pos_y][client->pos_x].linemate -= 1;
            client->inventory->linemate += 1;
            return dprintf(client->fd, "ok\n");
        } else
            return dprintf(client->fd, "ko\n");
    } else
        return take_player_next(server, client, args);
}
