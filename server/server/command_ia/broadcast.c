/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** broadcast.c
*/

#include "./include/command_ia.h"

int chnage_pos(client_t *client, int pos)
{
    int ret = pos;

    switch (client->orientation) {
        case 0:
            break;
        case 90:
            ret += 2;
            break;
        case 180:
            ret += 4;
            break;
        case 270:
            ret += 6;
            break;
        default:
            break;
    }
    if (ret > 8)
        ret -= 8;
    return ret;
}

int get_direction_end(client_t *tmp, client_t *client, bool revy, bool revx)
{
    if (tmp->pos_x == client->pos_x) {
        if (tmp->pos_y > client->pos_y || (tmp->pos_y < client->pos_y && revy))
            return chnage_pos(tmp, 5);
        else
            return chnage_pos(tmp, 1);
    }
    if (tmp->pos_y > client->pos_y || (tmp->pos_y < client->pos_y && revy)) {
        if (tmp->pos_x > client->pos_x || (tmp->pos_x < client->pos_x && revx))
            return chnage_pos(tmp, 8);
        else
            return chnage_pos(tmp, 6);
    } else {
        if (tmp->pos_x > client->pos_x || (tmp->pos_x < client->pos_x && revx))
            return chnage_pos(tmp, 2);
        else
            return chnage_pos(tmp, 4);
    }
}

int get_direction(client_t *tmp, client_t *client, server_t *server)
{
    bool revy = false;
    bool revx = false;
    int x_diff = abs(tmp->pos_x - client->pos_x);
    int y_diff = abs(tmp->pos_y - client->pos_y);

    if (tmp->pos_x == client->pos_x && tmp->pos_y == client->pos_y)
        return 0;
    if (x_diff > server->width / 2)
        revx = true;
    if (y_diff > server->height / 2)
        revy = true;
    if (tmp->pos_y == client->pos_y) {
        if (tmp->pos_x > client->pos_x || (tmp->pos_x < client->pos_x && revx))
            return chnage_pos(tmp, 7);
        else
            return chnage_pos(tmp, 3);
    }
    return get_direction_end(tmp, client, revy, revx);
}

void send_brodcast(client_t *client, int direction, char *message)
{
    dprintf(client->fd, "message %d, %s", direction, message);
}

int broadcast(char *command, server_t *server, client_t *client)
{
    client_t *tmp = server->clients;
    char **args = str_to_word_array(command, ' ');

    while (tmp != NULL) {
        if (tmp->id == client->id)
            continue;
        else
            send_brodcast(tmp, get_direction(tmp, client, server), args[1]);
    }
    return 0;
}
