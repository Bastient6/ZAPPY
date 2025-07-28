/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** init
*/

#include "../include/server.h"

void add_team(server_t *server, const char *name, int id, int maxClients)
{
    team_t *new_team = malloc(sizeof(team_t));
    team_t *current;

    new_team->name = strdup(name);
    new_team->id = id;
    new_team->NbClients = 0;
    new_team->maxClients = maxClients;
    new_team->next = NULL;
    if (server->teams == NULL)
        server->teams = new_team;
    else {
        current = server->teams;
        while (current->next != NULL)
            current = current->next;
        current->next = new_team;
    }
}

void init_arg(server_t *server, char **av)
{
    int i = 7;
    int j = 0;

    if (atoi(av[2]) < 1024 || atoi(av[2]) > 49151)
        exit(84);
    server->port = atoi(av[2]);
    server->width = atoi(av[4]);
    server->height = atoi(av[6]);
    for (; strcmp(av[i], "-n") != 0; i++);
    i++;
    for (; strcmp(av[i], "-c") != 0; i++)
        j++;
    server->teams = NULL;
    add_team(server, "GRAPHIC", 0, 1);
    for (int k = 0; k < j; k++)
        add_team(server, av[i - j + k], k + 1, atoi(av[i + 1]));
    server->nbteams = j;
    server->clientsNb = atoi(av[i + 1]);
    server->freq = atoi(av[i + 3]);
}
