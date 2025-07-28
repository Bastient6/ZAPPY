/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** clean_str
*/

#include "../include/server.h"

char *clean_str(char *str)
{
    int i = 0;
    int j = 0;
    char *new_str = malloc(sizeof(char) * strlen(str) + 1);

    if (new_str == NULL || str == NULL)
        return NULL;
    while (str[i] != '\0') {
        if (str[i] != '\t' && str[i] != '\n' && str[i] != '\r') {
            new_str[j] = str[i];
            j++;
        }
        i++;
    }
    new_str[j] = '\0';
    return new_str;
}
