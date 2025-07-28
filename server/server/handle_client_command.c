/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** handle_client_command
*/

#include "../include/server.h"

void do_command(server_t *serve, client_t *current_client)
{
    char *line;

    line = get_next_line(current_client->fd);
    if (line == NULL)
        return;
    append_command_mess(current_client, line, serve);
    free(line);
    (void)serve;
    return;
}

command_t *handle_client_command(server_t *serve, fd_set *read_fds)
{
    client_t *current_client = serve->clients;
    command_t *command = NULL;

    if (current_client == NULL)
        return NULL;
    while (current_client->next != NULL) {
        if (FD_ISSET(current_client->fd, read_fds))
            do_command(serve, current_client);
        current_client = current_client->next;
    }
    return command;
}
