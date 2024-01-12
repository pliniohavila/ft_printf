#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"


void    ft_putstr(const char*);
void	ft_putchar(char);

int     count_digits_in_base(int, int);
int     print_converted_n(int, int);
int     print_int(int);  // OK
int     print_char(char); // OK
int     print_str(const char*); // OK 
int     print_float(float); // OK 
int     print_octal(void); 
int     print_hex(void); 
int     print_pointer(void); 

int     main(void)
{
    int i = print_float(-42.24);
    printf("\n");
    int l = print_float(-42);
    printf("\ni: %d - l: %d\n", i, l);
    return (1);
}

int     print_int(int n)
{
    return print_converted_n(n, 10);
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

// Handle only float numbers with numbers which has two precision numbers
// This function is POV 
int     print_float(float f)
{
    int     aux;
    int     len;
    int     p_int;
    int     p_dec;
    
    // printf("f: %.2f\n", f);
    len = 0;
    if (f < 0)
    {
        f *= (-1);
        ft_putchar('-');
        len++;
    }
    aux = (int)(f * 100);
    p_int = (aux - ((aux % 100))) / 100;
    p_dec = aux % 100;
    len += print_converted_n(p_int, 10);
    ft_putchar('.');
    len++;
    len += print_converted_n(p_dec, 10);
    return (len);
}

int     print_converted_n(int nbr, int base)
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
	write(1, &c, 1);
}

void    ft_putstr(const char *str)
{
    while (*str != '\0') 
    {
        write(1, str, 1);
        str++;
    }
}
