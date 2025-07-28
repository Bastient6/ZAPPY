/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** get_client_by_team
*/

#include "../../include/server.h"

client_t *get_client_by_team(client_t *clients, int id)
{
    client_t *current = clients;

    while (current != NULL) {
        if (current->id_team == id)
            return current;
        current = current->next;
    }
    return NULL;
}
