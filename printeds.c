#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"


void    ft_putstr(const char *str);
void	ft_putchar(char c);

int     count_digits_in_base(int nbr, int base);
int     convert(int nbr, int base);
int     print_int(int n);  // OK
int     print_char(char c); // OK
int     print_str(const char *str); // OK 
int     print_float(float n); 
int     print_octal(void); 
int     print_hex(void); 
int     print_pointer(void); 

int     main(void)
{
    int i = print_str("ABC");
    printf("\n");
    int l = print_str("Plinio");
    printf("\ni: %d - l: %d\n", i, l);
    return (1);
}

int     print_int(int n)
{
    return convert(n, 10);
}

int     print_char(char c)
{
    ft_putchar(c);
    return (1);
}

int     print_str(const char *str)
{
    int     len;

    len = ft_strlen(str);
    ft_putstr(str);
    return (len);
}

int     convert(int nbr, int base)
{
    static char     digits[] = "0123456789ABCDEF";
    char            *converted;
    int             len;
    int             r;

    len = count_digits_in_base(nbr, base) + 1;
    converted = (char*)malloc(sizeof(char) * len + 1); 
    if (!converted)
        return (-1);
    if (nbr < 0) 
    {
        converted[0] = '-';
        nbr *= (-1);
    }
    else 
    {
        len--;
    }
    r = len;
    converted[len--] = '\0';
    if (nbr == 0)
        converted[len--] = '0';
    while (nbr != 0)
    {
        converted[len--] = digits[(nbr % base)];
        nbr /= base;
    }
    ft_putstr(converted);
    free(converted);
    return (r);
}

int     count_digits_in_base(int nbr, int base)
{
    int     count;

    count = 0;
    if (nbr == 0)
        return ++count;
    if (nbr < 0)
        nbr *= (-1);
    while (nbr != 0)
    {
        count++;
        nbr /= base;
    }
    return (count);
}

void	ft_putchar(char c)
{
	int	fd;

	fd = 1;
	write(fd, &c, 1);
}

void    ft_putstr(const char *str)
{
    // char    *letter;

    // letter = str;
    while (*str != '\0') 
    {
        write(1, str, 1);
        str++;
    }
}
