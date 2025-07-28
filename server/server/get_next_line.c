/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** get_next_line
*/

#include "../include/server.h"

#include <unistd.h>
#include <stdlib.h>

char *read_line(const int fd, char *line, char *tmp)
{
    char *buffer = malloc(sizeof(char) * (1024 + 1));
    int bytes_read = 0;
    int total_bytes_read = 0;

    bytes_read = read(fd, buffer + total_bytes_read, 1);
    while (bytes_read > 0) {
        if (buffer[total_bytes_read] == '\n') {
            buffer[total_bytes_read] = '\0';
            line = strdup(buffer);
            return line;
        }
        total_bytes_read++;
        if (total_bytes_read >= 1024) {
            tmp = realloc(buffer, sizeof(char) * (total_bytes_read + 1025));
            buffer = tmp;
        }
        bytes_read = read(fd, buffer + total_bytes_read, 1);
    }
    return buffer;
}

char *get_next_line(const int fd)
{
    char *buffer = malloc(sizeof(char) * (1024 + 1));
    char *line = NULL;
    char *tmp = NULL;

    buffer = read_line(fd, line, tmp);
    buffer[strlen(buffer)] = '\0';
    line = strdup(buffer);
    free(buffer);
    return line;
}
