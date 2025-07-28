/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** handle_command_graphic
*/

#include "../include/server.h"

int (*f_array_graphique[])
    (char *command, server_t *server, client_t *client) = {
    command_map_size, command_content_of_a_tile, command_map_content,
    command_name_teams, command_player_position, command_player_level,
    command_player_inventory, command_time_request, command_time_modification,
    command_new_player, command_expulsion, command_broadcast,
    command_incantation, NULL};

const char *f_name_graphique[] =
{"msz", "bct", "mct", "tna", "ppo", "plv", "pin", "sgt",
    "sst", "pnw", "pex", "pbc", "pic", NULL};

int handle_command_graphic
(server_t *server, client_t *current_client, char *line)
{
    char *cleaned_line = clean_str(line);

    if (current_client == NULL)
        return 1;
    printf("GRAPHIC COMMAND: %s\n", cleaned_line);
    for (int i = 0; f_name_graphique[i] != NULL; i++) {
        if (strncmp(cleaned_line, f_name_graphique[i], 3) == 0) {
            return (*f_array_graphique[i])
            (cleaned_line, server, current_client);
        }
    }
    return 1;
}
