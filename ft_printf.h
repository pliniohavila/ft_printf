#ifndef FT_PRINTF_H
#define FT_PRINTF_H

typedef int     (*fptr) (va_list);
typedef struct  spec_opt
{
    char        spec;
    fptr        spec_func;
}               SPEC_OPT;

int     ft_printf(const char *fmt, ...);
fptr    get_spec_func(char spec);
int     count_digits_in_base(int, int);
int     print_converted_n(int, int);
int     print_int(va_list);  
int     print_char(va_list); 
int     print_str(va_list);  
int     print_float(va_list);  
int     print_octal(va_list);  
int     print_hex(va_list);
int     print_pointer(va_list);

#endif