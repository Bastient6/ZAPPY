/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** command_broadcast
*/

#include "./include/command_gui.h"

int command_broadcast(char *command, server_t *server, client_t *client)
{
    char **args = str_to_word_array(command, ' ');
    char *msg;

    (void)server;
    for (int i = 2; args[i]; i++)
        msg = strdup(args[i]);
    return dprintf(client->fd, "pbc #%d %s\n", client->fd, msg);
}
