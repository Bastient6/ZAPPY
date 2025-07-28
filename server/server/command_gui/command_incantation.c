/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** command_incantation
*/

#include "./include/command_gui.h"

int command_incantation(char *command, server_t *server, client_t *client)
{
    char **args = str_to_word_array(command, ' ');
    client_t *current = get_client_by_id(server->clients, atoi(args[1]));
    client_t *tmp = server->clients;
    int ret = 0;

    ret = dprintf(client->fd, "pic %d %d %d", current->pos_x, current->pos_y,
        current->level);
    while (tmp != NULL) {
        if (tmp->id_team == current->id_team)
            ret = dprintf(client->fd, " #%d", tmp->fd);
        tmp = tmp->next;
    }
    ret = dprintf(client->fd, "\n");
    return ret;
}
