/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** server
*/

#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <time.h>
#include "../server/command_gui/include/command_gui.h"
#include "../server/command_ia/include/command_ia.h"


#ifndef SERVER_H_
    #define SERVER_H_
    #define FOOD 0.5
    #define LINEMATE 0.3
    #define DERAUMERE 0.15
    #define SIBUR 0.1
    #define MENDIANE 0.1
    #define PHIRAS 0.08
    #define THYSTAME 0.05

typedef struct s_command {
    char *command;
    double time;
    double time_exec;
    struct s_command *next;
} command_t;

typedef struct s_egg {
    int id_teams;
    int x;
    int y;
    struct s_egg *next;
} egg_t;

typedef struct content_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    int nb_playeur;
    int egg;
} content_t;


typedef struct s_client {
    int pos_x;
    int pos_y;
    int id;
    int orientation;
    int level;
    int fd;
    int id_team;
    int ret;
    struct s_command *commands;
    struct content_s *inventory;
    struct s_client *next;
} client_t;

typedef struct team_s {
    char *name;
    int NbClients;
    int maxClients;
    int id;
    struct team_s *next;
} team_t;

typedef struct server_s {
    int fd;
    int port;
    struct sockaddr_in sockaddr_in;
    socklen_t sockaddr_in_size;
    int width;
    int height;
    int clientsNb;
    int freq;
    int nbteams;
    int last_id;
    double time;
    team_t *teams;
    client_t *clients;
    egg_t *egg;
    content_t **content;
} server_t;

void init_arg(server_t *server, char **av);
void init_server(server_t *server);
void init_socket(server_t *server);
int start_server(const server_t *server);
void handle_all_clients(server_t *server);
client_t *client_add(client_t *head, client_t *new_client);
client_t *init_client(const int fd, int id_team, int id, server_t *server);
char *get_next_line(const int fd);
command_t *handle_client_command(server_t *serve, fd_set *read_fds);
char *clean_str(char *str);
int handle_command_graphic
(server_t *server, client_t *current_client, char *line);
int handle_command_ia(server_t *server, client_t *current_client, char *line);
void start_command(server_t *server, double time);
char **str_to_word_array(char *str, char separator);
client_t *get_client_by_id(client_t *head, int id);
char *get_name_team_by_id(server_t *server, int id);
char *my_itoa(int nb);
team_t *get_team_by_id(server_t *server, int id);
client_t *get_client_by_team(client_t *clients, int id);

void append_command_mess
(client_t *current_client, char *command, server_t *server);
void append_command(command_t *head, command_t *new_command);
void rm_list(command_t *head);
void rm_one(command_t *head);

int check_pos_player_x(server_t *server, int x);
int check_pos_player_y(server_t *server, int y);
void add_ressource(server_t *server);

egg_t *create_egg(int id_teams, int x, int y);
egg_t *append_egg(egg_t *head, int id_teams, server_t *server);
egg_t *delete_egg(egg_t *head, egg_t *to_delete);

char *my_strcat(char *dest, const char *new);

#endif /* !SERVER_H_ */
