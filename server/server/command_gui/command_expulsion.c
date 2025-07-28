/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** command_expulsion
*/

#include "./include/command_gui.h"

int command_expulsion(char *command, server_t *server, client_t *client)
{
    char **args = str_to_word_array(command, ' ');
    client_t *current = get_client_by_id(server->clients, atoi(args[1]));

    return dprintf(client->fd, "pex #%d\n", current->fd);
}
