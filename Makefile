CC 		= gcc
FLAGS	= -Wall -Wextra -Werror -g3


all: c_printf.c
	$(CC) -g3 c_printf.c -o c_printf

run: c_printf
	./c_printf

