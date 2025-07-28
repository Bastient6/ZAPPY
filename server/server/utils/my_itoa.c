/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** my_itoa
*/


#include "../../include/server.h"

char *my_itoa(int nb)
{
    int size = 0;
    int tmp = nb;
    char *str;

    for (size = 0; tmp > 0; size++)
        tmp /= 10;
    str = malloc(sizeof(char) * (size + 1));
    str[size] = '\0';
    for (int i = size - 1; i >= 0; i--) {
        str[i] = nb % 10 + '0';
        nb /= 10;
    }
    return str;
}
