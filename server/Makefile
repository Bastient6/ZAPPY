##
## EPITECH PROJECT, 2024
## B-YEP-400-MPL-4-1-zappy-thomas.janiaut
## File description:
## Makefile
##

SRC = main.c \
	$(wildcard server/command_gui/*.c)\
	$(wildcard server/command_ia/*.c)\
	$(wildcard server/utils/*.c)\
	$(wildcard server/*.c)\

OBJ = $(SRC:.c=.o)

NAME = ../zappy_server

CFLAGS = -Wall -Wextra -Werror -g3

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
