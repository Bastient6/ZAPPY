/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** command_name_teams
*/

#include "./include/command_gui.h"

int command_name_teams(char *command, server_t *server, client_t *client)
{
    team_t *current_team = server->teams;
    int ret = 0;

    (void)command;
    while (current_team) {
        if (strcmp(current_team->name, "GRAPHIC") == 0) {
            current_team = current_team->next;
            continue;
        }
        ret = dprintf(client->fd, "tna %s\n", current_team->name);
        current_team = current_team->next;
    }
    if (ret == -1)
        return -1;
    return 0;
}
