/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** move_player.c
*/


#include "./include/command_ia.h"

void check_pos_player(server_t *server, client_t *client)
{
    if (client->pos_x >= server->width)
        client->pos_x = 0;
    else if (client->pos_x < 0)
        client->pos_x = server->width - 1;
    if (client->pos_y >= server->height)
        client->pos_y = 0;
    else if (client->pos_y < 0)
        client->pos_x = server->height - 1;
}

client_t *move_orientation(client_t *client)
{
    switch (client->orientation) {
        case 1:
            client->pos_y += 1;
            break;
        case 2:
            client->pos_x += 1;
            break;
        case 3:
            client->pos_y -= 1;
            break;
        case 4:
            client->pos_x -= 1;
            break;
    }
    return client;
}

int move_playeur(char *command, server_t *server, client_t *client)
{
    char ppo[10] = "ppo ";

    (void) command;
    server->content[client->pos_x][client->pos_y].nb_playeur -= 1;
    client = move_orientation(client);
    check_pos_player(server, client);
    server->content[client->pos_x][client->pos_y].nb_playeur += 1;
    strcat(ppo, my_itoa(client->id));
    strcat(ppo, "\n");
    handle_command_graphic
    (server, get_client_by_team(server->clients, 0), ppo);
    return dprintf(client->fd, "ok\n");
}
