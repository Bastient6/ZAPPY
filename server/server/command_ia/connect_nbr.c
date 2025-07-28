/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** Connect_nbr.c
*/

#include "./include/command_ia.h"

team_t *find_team(server_t *server, client_t *client)
{
    team_t *tmp = server->teams;

    while (tmp != NULL) {
        if (tmp->id == client->id_team)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

int connect_nbr(char *command, server_t *server, client_t *client)
{
    team_t *team = find_team(server, client);

    (void) command;
    if (team == NULL)
        return dprintf(client->fd, "ko\n");
    return dprintf(client->fd, "%d\n", team->maxClients - team->NbClients);
}
