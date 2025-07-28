/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** handle_clients
*/

#include "../include/server.h"
#include <time.h>

static double current_time_in_millis(void)
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1000000.0;
}

static void signal_handler(int signal)
{
    if (signal == SIGINT)
        exit(0);
}

int loop(fd_set *read_fds, int max_fd, server_t *server)
{
    client_t *current_client = server->clients;
    struct timeval timeout = {0, 0};

    FD_ZERO(read_fds);
    FD_SET(server->fd, read_fds);
    if (current_client == NULL) {
        if (select(max_fd + 1, read_fds, NULL, NULL, &timeout) == -1)
            perror("select");
        return max_fd;
    }
    while (current_client != NULL) {
        FD_SET(current_client->fd, read_fds);
        if (current_client->fd > max_fd)
            max_fd = current_client->fd;
        current_client = current_client->next;
    }
    if (select(max_fd + 1, read_fds, NULL, NULL, &timeout) == -1)
        perror("select");
    return max_fd;
}

void send_command(server_t *server, client_t *new_client)
{
    if (new_client->id_team == 0) {
        handle_command_graphic(server, new_client, "msz\n");
        handle_command_graphic(server, new_client, "sgt\n");
        handle_command_graphic(server, new_client, "tna\n");
    } else {
        dprintf(new_client->fd, "%d\n%d %d\n", new_client->id_team,
        server->width, server->height);
        dprintf(get_client_by_team(server->clients, 0)->fd, "pnw %i %i %i %i %i %s\n", new_client->id,
        new_client->pos_x, new_client->pos_y, new_client->orientation,
        new_client->level, get_name_team_by_id
        (server, new_client->id_team));
    }
}

void add_client(server_t *server, int socket, char *team)
{
    client_t *new_client;

    if (team == NULL)
        return;
    for (team_t *current = server->teams; current != NULL;
    current = current->next) {
        if (strcmp(current->name, team) == 0 &&
        current->NbClients < current->maxClients) {
            new_client =
            init_client(socket, current->id, server->last_id, server);
            server->clients = client_add(server->clients, new_client);
            server->last_id++;
            current->NbClients++;
            send_command(server, new_client);
            break;
        }
    }
}

void new_clients(server_t *server, fd_set *read_fds)
{
    int client_socket = -1;
    char *team = NULL;

    if (FD_ISSET(server->fd, read_fds)) {
        client_socket = accept(server->fd, (struct sockaddr *)
        &server->sockaddr_in, (socklen_t *) &server->sockaddr_in_size);
        if (client_socket == -1)
            perror("accept");
        printf("New client connected\n");
        dprintf(client_socket, "WELCOME\n");
        team = clean_str(get_next_line(client_socket));
        if (team == NULL) {
            close(client_socket);
            return;
        }
        add_client(server, client_socket, team);
        printf("Client added to team %s\n", team);
        free(team);
    }
}

void handle_all_clients(server_t *server)
{
    fd_set read_fds;
    long long start_time = current_time_in_millis();
    int max_fd = server->fd;

    add_ressource(server);
    while (true) {
        signal(SIGINT, signal_handler);
        FD_ZERO(&read_fds);
        FD_SET(server->fd, &read_fds);
        max_fd = server->fd;
        if (loop(&read_fds, max_fd, server) != -1)
            new_clients(server, &read_fds);
        handle_client_command(server, &read_fds);
        start_command(server, current_time_in_millis() - start_time);
        handle_command_graphic
        (server, get_client_by_team(server->clients, 0), "mct\n");
        start_time = current_time_in_millis();
    }
}
