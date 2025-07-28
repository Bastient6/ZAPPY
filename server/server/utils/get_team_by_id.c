/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** get_team_by_id
*/

#include "../../include/server.h"

team_t *get_team_by_id(server_t *server, int id)
{
    team_t *current = server->teams;

    while (current != NULL) {
        if (current->id == id)
            return current;
        current = current->next;
    }
    return NULL;
}
