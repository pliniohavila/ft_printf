#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int _printf(const char* format, ...);

int _putchar(char c)
{
    if (!c)
        return (write(1, '', 1));
    return (write(1, &c, 1));
}

int     main(void)
{
    int returns;

    returns = 0;
    returns = printf("hello %, how are you\n");
    printf("printf returns value: %d\n", returns);
    _putchar('a');
    printf("\n");
    _putchar(NULL);
    printf("\n");
    _putchar('b');
    // returns = _printf(NULL);
    // printf("_printf returns value: %d\n", returns);
    return (0);
}