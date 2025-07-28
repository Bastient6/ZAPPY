/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** command_player_inventory
*/


#include "./include/command_gui.h"

int command_player_inventory(char *command, server_t *server, client_t *client)
{
    char **new_command = str_to_word_array(command, ' ');
    client_t *current =
    get_client_by_id(server->clients, atoi(new_command[1]));

    return dprintf(client->fd, "pin %d %d %d %d %d %d %d %d %d %d\n",
        current->id, current->pos_x, current->pos_y, current->inventory->food,
        current->inventory->linemate, current->inventory->deraumere,
        current->inventory->sibur, current->inventory->mendiane,
        current->inventory->phiras, current->inventory->thystame);
}
