/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** init_client
*/

#include "../include/server.h"

client_t *init_inventory(client_t *new)
{
    new->inventory = malloc(sizeof(content_t));
    new->inventory->food = 10;
    new->inventory->linemate = 0;
    new->inventory->deraumere = 0;
    new->inventory->sibur = 0;
    new->inventory->mendiane = 0;
    new->inventory->phiras = 0;
    new->inventory->thystame = 0;
    new->commands = NULL;
    return new;
}

client_t *init_client(const int fd, int id_team, int id, server_t *server)
{
    client_t *new = malloc(sizeof(client_t));
    egg_t *egg = server->egg;

    if (new == NULL)
        return NULL;
    new->fd = fd;
    new->id_team = id_team;
    new->pos_x = 0;
    new->pos_y = 0;
    if (id_team != 0) {
        while (egg != NULL && egg->id_teams != id_team) {
            egg = egg->next;
        }
        new->pos_x = egg->x;
        new->pos_y = egg->y;
    }
    new->orientation = rand() % 4;
    new->level = 1;
    new->id = id;
    new->ret = 0;
    new->next = NULL;
    return init_inventory(new);
}

client_t *client_add(client_t *head, client_t *new_client)
{
    client_t *current = head;

    if (current == NULL) {
        return new_client;
    }
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_client;
    return head;
}
