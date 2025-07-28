/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** start_server
*/

#include "../include/server.h"

void print_info_server(const server_t *server)
{
    printf("Server started on port %d\n", server->port);
    printf("Server started with %d clients\n", server->clientsNb);
    printf("Server started with %d teams\n", server->nbteams);
    printf("Server started with %d width\n", server->width);
    printf("Server started with %d height\n", server->height);
    printf("Server started with %d freq\n", server->freq);
}

int start_server(const server_t *server)
{
    if (bind(server->fd, (struct sockaddr *)
    &server->sockaddr_in, sizeof(server->sockaddr_in)) == -1) {
        perror("bind()");
        exit(84);
    }
    if (listen(server->fd, (server->clientsNb * server->nbteams + 1)) == -1) {
        perror("listen()");
        exit(84);
    }
    print_info_server(server);
    return 0;
}
