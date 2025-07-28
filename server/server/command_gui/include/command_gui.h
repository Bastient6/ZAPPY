/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** command
*/

#ifndef COMMAND_H_
    #define COMMAND_H_
    #include "../../../include/server.h"

int command_map_size(char *command, server_t *server, client_t *client);
int command_content_of_a_tile
(char *command, server_t *server, client_t *client);
int command_map_content(char *command, server_t *server, client_t *client);
int command_name_teams(char *command, server_t *server, client_t *client);
int command_player_position(char *command, server_t *server, client_t *client);
int command_player_level(char *command, server_t *server, client_t *client);
int command_player_inventory
(char *command, server_t *server, client_t *client);
int command_time_request(char *command, server_t *server, client_t *client);
int command_time_modification
(char *command, server_t *server, client_t *client);
int command_new_player(char *command, server_t *server, client_t *client);
int command_expulsion(char *command, server_t *server, client_t *client);
int command_broadcast(char *command, server_t *server, client_t *client);
int command_incantation(char *command, server_t *server, client_t *client);

#endif /* !COMMAND_H_ */
