/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** command
*/

#ifndef COMMAND_IA_H_
    #define COMMAND_IA_H_
    #include "../../../include/server.h"

int broadcast(char *command, server_t *server, client_t *client);
int connect_nbr(char *command, server_t *server, client_t *client);
int drop_playeur(char *command, server_t *server, client_t *client);
int eject_player(char *command, server_t *server, client_t *client);
int fork_player(char *command, server_t *server, client_t *client);
int inventoy_player(char *command, server_t *server, client_t *client);
int look(char *command, server_t *server, client_t *client);
int move_playeur(char *command, server_t *server, client_t *client);
int rotate_playeur_right(char *command, server_t *server, client_t *client);
int rotate_playeur_left(char *command, server_t *server, client_t *client);
int take_playeur(char *command, server_t *server, client_t *client);


#endif /* !COMMAND_IA_H_ */
