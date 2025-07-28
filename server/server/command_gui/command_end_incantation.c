/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** command_end_incantation
*/

#include "./include/command_gui.h"

// command doit contenit "pie x y Résult of incantation"

int command_end_incantation(char *command, server_t *server, client_t *client)
{
    char **args = str_to_word_array(command, ' ');

    (void)server;
    return dprintf(client->fd, "pie %s %s %s\n", args[1], args[2], args[3]);
}
