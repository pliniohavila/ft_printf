#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

typedef int     (*fptr) (void);
typedef struct  spec_opt
{
    char        spec;
    fptr        spec_func;
}               SPEC_OPT;

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

void	ft_putchar(char c)
{
	int	fd;

	fd = 1;
	write(fd, &c, 1);
}

void    ft_putstr(char *str)
{
    char    *letter;
    int     space;

    letter = str;
    space = 32;
    while (*letter != '\0') 
    {
        write(1, letter, 1);
        // write(1, &space, 1);
        letter++;
    }
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

int     print_int(void)
{
    ft_putstr("[int specifier]");
    return (1);
}

int     print_char(void)
{
    ft_putstr("[char specifier]");
    return (1);
}

int     print_str(void)
{
    ft_putstr("[string specifier]");
    return (1);
}

int     print_float(void)
{
    ft_putstr("[float specifier]");
    return (1);
}

int     print_octal(void)
{
    ft_putstr("[octal specifier]");
    return (1);
}

int     print_hex(void)
{
    ft_putstr("[hex specifier]");
    return (1);
}

int     print_pointer(void)
{
    ft_putstr("[pointer specifier]");
    return (1);
}