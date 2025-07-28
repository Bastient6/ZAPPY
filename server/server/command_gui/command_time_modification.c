/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** command_time_modification
*/

#include "./include/command_gui.h"

int command_time_modification
(char *command, server_t *server, client_t *client)
{
    char **new_command = str_to_word_array(command, ' ');

    server->freq = atoi(new_command[1]);
    return dprintf(client->fd, "sgt %d\n", server->freq);
}
