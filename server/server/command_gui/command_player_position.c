/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** command_player_position
*/

#include "./include/command_gui.h"

int command_player_position(char *command, server_t *server, client_t *client)
{
    char **new_command = str_to_word_array(command, ' ');
    client_t *current_client =
    get_client_by_id(server->clients, atoi(new_command[1]));

    if (current_client == NULL)
        return dprintf(client->fd, "ko\n");
    return dprintf(client->fd, "ppo %d %d %d %d\n", current_client->id,
    current_client->pos_x, current_client->pos_y, current_client->orientation);
}
