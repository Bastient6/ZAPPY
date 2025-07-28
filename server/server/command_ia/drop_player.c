/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** drop_player.c
*/

#include "./include/command_ia.h"

int drop_player_end(server_t *server, client_t *client, char **args)
{
    if (strcmp(args[1], "thystame")) {
        if (client->inventory->thystame > 0) {
            client->inventory->thystame -= 1;
            server->content[client->pos_y][client->pos_x].thystame += 1;
            return dprintf(client->fd, "ok\n");
        } else
            return dprintf(client->fd, "ko\n");
    } else
        return dprintf(client->fd, "ko\n");
}

int drop_player_next_bis(server_t *server, client_t *client, char **args)
{
    if (strcmp(args[1], "mendiane")) {
        if (client->inventory->mendiane > 0) {
            client->inventory->mendiane -= 1;
            server->content[client->pos_y][client->pos_x].mendiane += 1;
            return dprintf(client->fd, "ok\n");
        } else
            return dprintf(client->fd, "ko\n");
    }
    if (strcmp(args[1], "phiras")) {
        if (client->inventory->phiras > 0) {
            client->inventory->phiras -= 1;
            server->content[client->pos_y][client->pos_x].phiras += 1;
            return dprintf(client->fd, "ok\n");
        } else
            return dprintf(client->fd, "ko\n");
    } else
        return drop_player_end(server, client, args);
}

int drop_player_next(server_t *server, client_t *client, char **args)
{
    if (strcmp(args[1], "deraumere")) {
        if (client->inventory->deraumere > 0) {
            client->inventory->deraumere -= 1;
            server->content[client->pos_y][client->pos_x].deraumere += 1;
            return dprintf(client->fd, "ok\n");
        } else
            return dprintf(client->fd, "ko\n");
    }
    if (strcmp(args[1], "sibur")) {
        if (client->inventory->sibur > 0) {
            client->inventory->sibur -= 1;
            server->content[client->pos_y][client->pos_x].sibur += 1;
            return dprintf(client->fd, "ok\n");
        } else
            return dprintf(client->fd, "ko\n");
    } else
        return drop_player_next_bis(server, client, args);
}

int drop_playeur(char *command, server_t *server, client_t *client)
{
    char **args = str_to_word_array(command, ' ');

    (void) command;
    if (strcmp(args[1], "food")) {
        if (client->inventory->food > 0) {
            client->inventory->food -= 1;
            server->content[client->pos_y][client->pos_x].food += 1;
            return dprintf(client->fd, "ok\n");
        } else
            return dprintf(client->fd, "ko\n");
    }
    if (strcmp(args[1], "linemate")) {
        if (client->inventory->linemate > 0) {
            client->inventory->linemate -= 1;
            server->content[client->pos_y][client->pos_x].linemate += 1;
            return dprintf(client->fd, "ok\n");
        } else
            return dprintf(client->fd, "ko\n");
    } else
        return drop_player_next(server, client, args);
}
