#ifndef FT_PRINTF_H
#define FT_PRINTF_H


typedef int     (*fptr) (void);
typedef struct  spec_opt
{
    char        spec;
    fptr        spec_func;
}               SPEC_OPT;


int     ft_printf(const char *fmt, ...);
fptr    get_spec_func(char spec);
int     count_digits_in_base(int, int);
int     print_converted_n(int, int);
int     print_int(int);  
int     print_char(char); 
int     print_str(const char*);  
int     print_float(float);  
int     print_octal(int);  
int     print_hex(int);  
int     print_pointer(void*);

#endif