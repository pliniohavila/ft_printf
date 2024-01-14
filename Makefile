CC 		= gcc
FLAGS	= -Wall -Wextra -Werror -g3
SANIT	= -fsanitize=address

all: ft_printf.c
	$(CC) -g3 ft_printf.c -L. -lft -o ft_printf

run: ft_printf
	./ft_printf

printeds:
	$(CC) -g3 printeds.c -L. -lft -o printeds

runp:
	./printeds