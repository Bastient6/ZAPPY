/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** command_time_request
*/

#include "./include/command_gui.h"

int command_time_request(char *command, server_t *server, client_t *client)
{
    (void)command;
    return dprintf(client->fd, "sgt %d\n", server->freq);
}
