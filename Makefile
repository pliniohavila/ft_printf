CC 		= gcc
FLAGS	= -Wall -Wextra -Werror -g3

all: ft_printf.c
	$(CC) -g3 ft_printf.c -o ft_printf

run: ft_printf
	./ft_printf
