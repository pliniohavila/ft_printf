#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"


int     ft_printf(const char *fmt, ...);
void    ft_putstr(char *str);
void	ft_putchar(char c);
fptr    get_spec_func(char spec);
int     print_int(void); 
int     print_char(void); 
int     print_str(void); 
int     print_float(void); 
int     print_octal(void); 
int     print_hex(void); 
int     print_pointer(void); 

int     main(void)
{
    // char    *str;

    // str = "Hello world!\n";
    // ft_printf(str);
    ft_printf("Ola char: %c int: %d te float: %f string: %s pointer: %p\n");
    ft_printf("Ola char: %c%d te float: %fstring: %s pointer: %p\n");
    return (1);
}

// handle with %d, %c, %s, %f, %o, %x, %p
int     ft_printf(const char *fmt, ...)
{
    int     i;
    int     count_printed;
    fptr    print_func;

    i = 0; 
    count_printed = 0;
    if (fmt == NULL && (fmt[i] == '%' && fmt[i+1] == '\0'))
        return (-1);
    while (fmt[i] != '\0')
    {
        print_func = NULL;
        if (fmt[i] == '%')
        {
            if (fmt[i + 1] == '%')
            {
                i++; 
                ft_putchar(fmt[i]);       
            }
            else 
            {
                print_func = get_spec_func(fmt[i + 1]);
                print_func();
                if (!print_func)
                    return (-1);
                i++; 
            }
        }
        else 
        {
            ft_putchar(fmt[i]);
        }
        i++;
        count_printed++;
    }
    return (count_printed);
}

fptr    get_spec_func(char spec)
{
    int         i;
    SPEC_OPT    spec_opts[7] = {
        {'d', print_int}, 
        {'c', print_char}, 
        {'s', print_str}, 
        {'f', print_float}, 
        {'o', print_octal}, 
        {'x', print_hex}, 
        {'p', print_pointer}, 
    }; 

    i = 0;
    while (i < 7)
    {
        if (spec == spec_opts[i].spec)
            return (spec_opts[i].spec_func);
        i++;
    }   
    return (NULL);
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
    if ((len == 0) || (!str))
    {
        ft_putstr("(null)");
        return (6);
    }
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

int     print_octal(int n)
{
    int     len;

    len = 0;
    ft_putstr("0o");
    len += (2 + print_converted_n(n, 8));
    return (len);
}

int     print_hex(int n)
{
    int     len;

    len = 0;
    ft_putstr("0x");
    len += (2 + print_converted_n(n, 16));
    return (len);
}

int     print_pointer(void *address_pointer)
{
    uintptr_t   address_int;
    char        address[16];
    int         i;

    address_int = (uintptr_t)address_pointer;
    i = 0;
    while (i++ < 16) 
    {
        address[15 - i] = "0123456789abcdef"[address_int & 0xf];
        address_int >>= 4;
    }
    ft_putstr("0x");
    ft_putstr(address);
    return (18);
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