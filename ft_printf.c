#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

int     ft_printf(const char *fmt, ...);

int     main(void)
{
    char    *str;

    str = "Hello world!\n";
    int c = ft_printf(str);
    printf("Printed %s with %d characters\n", str, c);
}

void	ft_putchar(char c)
{
	int	fd;

	fd = 1;
	write(fd, &c, 1);
}


// handle with %d, %c, %s, %f, %o, %x, %p
int     ft_printf(const char *fmt, ...)
{
    int     i;
    int     count_printed;

    i = 0; 
    count_printed = 0;
    if (fmt == NULL && (fmt[i] == '%' && fmt[i+1] == '\0'))
        return (-1);

    while (fmt[i] != '\0')
    {
        ft_putchar(fmt[i]);
        i++;
        count_printed++;
    }
    return (count_printed);
}