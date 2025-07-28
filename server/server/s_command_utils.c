/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** s_command_utils.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/server.h"


int find_time_mess_biss(char *command)
{
    if (strcmp(command, "Fork") == 0)
        return 42;
    if (strcmp(command, "Take object") == 0)
        return 7;
    if (strcmp(command, "Set object") == 0)
        return 7;
    if (strcmp(command, "Look") == 0)
        return 7;
    if (strcmp(command, "Incantation") == 0)
        return 300;
    return 0;
}

int find_time_mess(char *command)
{
    if (strcmp(command, "Forward") == 0)
        return 7;
    if (strcmp(command, "Right") == 0)
        return 7;
    if (strcmp(command, "Left") == 0)
        return 7;
    if (strcmp(command, "Look") == 0)
        return 7;
    if (strcmp(command, "Inventory") == 0)
        return 1;
    if (strcmp(command, "Broadcast text") == 0)
        return 7;
    if (strcmp(command, "Eject") == 0)
        return 7;
    return find_time_mess_biss(command);
}

void append_command_mess
(client_t *current_client, char *command, server_t *server)
{
    command_t *new_command = malloc(sizeof(command_t));
    command_t *last = current_client->commands;
    int nb = 0;

    new_command->command = strdup(command);
    new_command->time = find_time_mess(command) / server->freq;
    printf("timessss = %f\n", new_command->time);
    new_command->next = NULL;
    if (last == NULL) {
        last = new_command;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
        nb++;
        if (nb >= 10)
            return;
    }
    last->next = new_command;
}
