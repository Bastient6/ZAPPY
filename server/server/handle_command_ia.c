/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** handle_command_ia
*/

#include "../include/server.h"

int (*f_array_ia[])
    (char *command, server_t *server, client_t *client) = {
    move_playeur, rotate_playeur_right, rotate_playeur_left,
    look, inventoy_player, broadcast, connect_nbr, fork_player,
    eject_player, take_playeur, drop_playeur, NULL};

const char *f_name_ia[] =
{"Forward", "Right", "Left", "Look", "Inventory", "Broadcast text",
    "Connect_nbr", "Fork", "Eject", "Take object", "Set object", NULL};

int handle_command_ia
(server_t *server, client_t *current_client, char *line)
{
    char *cleaned_line = clean_str(line);

    for (int i = 0; f_name_ia[i] != NULL; i++) {
        if (strncmp(cleaned_line, f_name_ia[i], 3) == 0) {
            printf("IA COMMAND: %s\n", cleaned_line);
            return (*f_array_ia[i])
            (cleaned_line, server, current_client);
        }
    }
    return 1;
}
