#include <stdio.h>
#include <stdlib.h>

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

int     convert_base_str(int nbr, int base)
{
    static char     digits[] = "0123456789abcdef0123456789ABCDEF";
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
    printf(converted);
    free(converted);
    return (r);
}

int main()
{
    printf(" -> [0]d: %d\n", convert_base_str(0, 10));
    printf(" -> [42]d: %d\n", convert_base_str(42, 10));
    printf(" -> [-42]h: %d\n", convert_base_str(-42, 10));
    printf(" -> [145]h: %d\n", convert_base_str(145, 16));
    printf(" -> [145]h: %d\n", convert_base_str(145, 16));
    printf(" -> [1]h: %d\n", convert_base_str(1, 16));
    printf(" -> [42]o: %d\n", convert_base_str(42, 8));
    printf(" -> [4]o: %d\n", convert_base_str(4, 8));

    return 0;
}
