/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** egg_utilis.c
*/

#include "../../include/server.h"

egg_t *create_egg(int id_teams, int x, int y)
{
    egg_t *new_egg = malloc(sizeof(egg_t));

    if (new_egg == NULL) {
        return NULL;
    }
    new_egg->id_teams = id_teams;
    new_egg->x = x;
    new_egg->y = y;
    return new_egg;
}

egg_t *append_egg(egg_t *head, int id_teams, server_t *server)
{
    egg_t *new_egg = malloc(sizeof(egg_t));
    egg_t *current = head;

    new_egg = create_egg(id_teams, rand() % server->width, rand() % server->height);
    if (current == NULL) {
        return new_egg;
    }
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_egg;
    return head;
}

egg_t *delete_egg(egg_t *head, egg_t *egg)
{
    egg_t *tmp;

    if (head == egg) {
        head = egg->next;
        free(egg);
        return head;
    }
    tmp = head;
    while (tmp->next != egg && tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = egg->next;
    free(egg);
    return tmp;
}