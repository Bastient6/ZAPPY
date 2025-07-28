/*
** EPITECH PROJECT, 2024
** B-YEP-400-MPL-4-1-zappy-thomas.janiaut
** File description:
** main
*/

#include "./include/server.h"

int print_help(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height ");
    printf("-n name1 name2 ... -c clientsNb -f freq\n");
    printf("\tport\tis the port number\n");
    printf("\twidth\tis the width of the world\n");
    printf("\theight\tis the height of the world\n");
    printf("\tnameX\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf("\tfreq\tis the reciprocal of time unit ");
    printf("for execution of actions\n");
    return 0;
}

int main(int ac, char **av)
{
    server_t server;

    if (ac < 2)
        return 84;
    if (strcmp(av[1], "-help") == 0)
        return print_help();
    if (ac < 7)
        return 84;
    init_arg(&server, av);
    init_server(&server);
    start_server(&server);
    handle_all_clients(&server);
    return 0;
}
