/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** enject_player.c
*/

#include "./include/command_ia.h"

void eject(client_t *ceject, client_t *player, server_t *server)
{
    server->content[ceject->pos_y][ceject->pos_x].nb_playeur -= 1;
    switch (player->orientation) {
        case 0:
            ceject->pos_y = check_pos_player_y(server, ceject->pos_y + 1);
            dprintf(ceject->fd, "eject : N\n");
            break;
        case 90:
            ceject->pos_x = check_pos_player_x(server, ceject->pos_x + 1);
            dprintf(ceject->fd, "eject : E\n");
            break;
        case 180:
            ceject->pos_y = check_pos_player_y(server, ceject->pos_y - 1);
            dprintf(ceject->fd, "eject : S\n");
            break;
        case 270:
            ceject->pos_x = check_pos_player_x(server, ceject->pos_x - 1);
            dprintf(ceject->fd, "eject : O\n");
            break;
    }
    server->content[ceject->pos_y][ceject->pos_x].nb_playeur += 1;
}

// a revoir
int eject_player(char *command, server_t *server, client_t *client)
{
    client_t *tmp = server->clients;

    (void) command;
    if (server->content[client->pos_x][client->pos_y].nb_playeur == 0)
        return dprintf(client->fd, "ok\n");
    while (tmp != NULL) {
        if (tmp->pos_x == client->pos_x && tmp->pos_y == client->pos_y) {
            eject(tmp, client, server);
        }
        tmp = tmp->next;
    }
    return dprintf(client->fd, "ok\n");
}
