/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** str_to_word_array
*/

#include "../../include/server.h"

static size_t count_char(char *str, char separator)
{
    size_t count = 0;

    for (size_t i = 0; str[i]; i++)
        if (str[i] == separator)
            count++;
    return count;
}

char **str_to_word_array(char *str, char separator)
{
    int array_size = count_char(str, separator) + 2;
    char **array = malloc(sizeof(char *) * array_size);
    char *token;

    if (array_size != 0  && str != NULL) 
        token = strtok(str, &separator);
    if (!array)
        return NULL;
    for (int i = 0; token; i++) {
        array[i] = strdup(token);
        token = strtok(NULL, &separator);
    }
    array[array_size - 1] = NULL;
    return array;
}
