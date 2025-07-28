/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** start_command.c
*/

#include "../include/server.h"

command_t *del_command(client_t *current_client, command_t *current_command)
{
    command_t *tmp;

    if (current_client->commands == current_command) {
        current_client->commands = current_command->next;
        free(current_command);
        return current_client->commands;
    }
    tmp = current_client->commands;
    while (tmp->next != current_command && tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = current_command->next;
    free(current_command);
    return tmp;
}

void start(server_t *server, client_t *current_client,
    command_t *current_command, double time)
{
    if (current_command->time <= 0) {
        if (current_client->id_team != 0) {
            handle_command_ia(server, current_client,
            current_command->command);
            current_client->commands =
            del_command(current_client, current_command);
        } else {
            handle_command_graphic
            (server, current_client, current_command->command);
            current_client->commands =
            del_command(current_client, current_command);
        }
    } else {
        current_command->time -= time;
    }
}

// a refaire a la fin
void start_command(server_t *server, double time)
{
    client_t *current_client = server->clients;
    command_t *current_command;

    server->time -= time;
    if (server->time <= 0) {
        server->time = 20 / server->freq;
        add_ressource(server);
    }
    while (current_client != NULL) {
        current_command = current_client->commands;
        if (current_command == NULL) {
            current_client = current_client->next;
            continue;
        }
        while (current_command->next != NULL) {
            start(server, current_client, current_command, time);
            current_command = current_command->next;
        }
        current_client = current_client->next;
    }
}
