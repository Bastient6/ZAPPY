##
## EPITECH PROJECT, 2024
## B-YEP-400-MPL-4-1-zappy-thomas.janiaut
## File description:
## Makefile
##

all:
	make -C server
	make -C gui
	make -C IA

clean:
	make clean -C server
	make clean -C gui
	make clean -C IA

fclean:
	make fclean -C server
	make fclean -C gui
	make fclean -C IA

re:
	make re -C server
	make re -C gui
	make re -C IA
