/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** get_name_team_by_id
*/

#include "../../include/server.h"

char *get_name_team_by_id(server_t *server, int id)
{
    team_t *current = server->teams;

    while (current != NULL) {
        if (current->id == id)
            return current->name;
        current = current->next;
    }
    return "nop";
}
