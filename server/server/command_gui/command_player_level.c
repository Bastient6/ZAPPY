/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** command_player_level
*/

#include "./include/command_gui.h"

int command_player_level(char *command, server_t *server, client_t *client)
{
    char **new_command = str_to_word_array(command, ' ');
    client_t *current =
    get_client_by_id(server->clients, atoi(new_command[1]));

    return dprintf(client->fd, "plv %d %d\n", client->id, current->level);
}
