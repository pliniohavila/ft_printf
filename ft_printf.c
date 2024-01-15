#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"


int     main(void)
{
    char    *str;
    int     len;
    double  d;
    int     i;
    int     l;

    str = "Hello world!";
    len = (int)ft_strlen(str);
    i = printf("PRINTF> STR: %s - CHAR: %c - LEN: %d - PTR: %p\n",  str, str[0], len, str);
    l = ft_printf("FT_PRINTF> STR: %s - CHAR: %c - LEN: %d - PTR: %p\n",  str, str[0], len, str);
    printf("i: %d - l: %d\n\n", i, l);
    d = 42.42;
    i = printf("PRINTF> D+: %.2f - D-: %.2f\n", d, -d);
    l = ft_printf("FT_PRINTF> D+: %f - D-: %f\n", d, -d);
    printf("i: %d - l: %d\n\n", i, l);
    return (0);
}

int     ft_printf(const char *fmt, ...)
{
    int     i;
    int     count_printed;
    fptr    print_func;
    va_list argptr;

    i = 0; 
    count_printed = 0;
    if (fmt == NULL && (fmt[i] == '%' && fmt[i+1] == '\0'))
        return (-1);
    va_start(argptr, fmt);
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
                if (!print_func)
                    return (-1);
                count_printed += print_func(argptr);
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
    va_end(argptr);
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


int     print_int(va_list argptr)
{
    int     n;

    n = va_arg(argptr, int);
    return print_converted_n(n, 10);
}

int     print_char(va_list argptr)
{
    char    c;

    c = (char)va_arg(argptr, int);
    ft_putchar(c);
    return (1);
}

int     print_str(va_list argptr)
{
    int     len;
    char    *str;

    str = va_arg(argptr, char*);
    len = ft_strlen(str);
    if ((len == 0) || (!str))
    {
        ft_putstr("(null)");
        return (6);
    }
    ft_putstr(str);
    return (len);
}

// // Handle only float numbers with numbers which has two precision numbers
// // This function is POV 
int     print_float(va_list argptr)
{
    int     aux;
    int     len;
    int     p_int;
    int     p_dec;
    double  f;

    f = va_arg(argptr, double);
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

int     print_octal(va_list argptr)
{
    int     n;
    int     len;

    n = va_arg(argptr, int);
    len = 0;
    ft_putstr("0o");
    len += (2 + print_converted_n(n, 8));
    return (len);
}

int     print_hex(va_list argptr)
{
    int     n;
    int     len;

    n = va_arg(argptr, int);
    len = 0;
    ft_putstr("0x");
    len += (2 + print_converted_n(n, 16));
    return (len);
}

int     print_pointer(va_list argptr)
{
    uintptr_t   pointer_int;
    char        address[16];
    int         i;
    void        *pointer;

    pointer = va_arg(argptr, void*);
    pointer_int = (uintptr_t)pointer;
    i = 0;
    while (i++ < 16) 
    {
        address[15 - i] = "0123456789abcdef"[pointer_int & 0xf];
        pointer_int >>= 4;
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