/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** command_pnw
*/

#include "./include/command_gui.h"

int command_new_player(char *command, server_t *server, client_t *client)
{
    char **args = str_to_word_array(command, ' ');
    client_t *new_client = get_client_by_id(server->clients, atoi(args[1]));

    if (new_client == NULL)
        return dprintf(client->fd, "ko\n");
    return dprintf(client->fd, "pnw %i %i %i %i %i %s\n", new_client->id,
        new_client->pos_x, new_client->pos_y, new_client->orientation,
        new_client->level, get_name_team_by_id
        (server, new_client->id_team));
}
