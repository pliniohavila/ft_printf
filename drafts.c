
// char    *ft_itoa(int n)
// {
//     int     count_dgts;
//     int     negative;
//     char    *itoa;

//     if (n == 0) return "0";
//     negative = 0;
//     count_dgts = 0;
//     if (n < 0)
//     {
//         negative = 1;
//         count_dgts++;
//         n = n * (-1);
//     }
//     count_dgts += (count_digits_in_base(n, 10));   
//     itoa = (char*)malloc(sizeof(char) * count_dgts);
//     if (!itoa) 
//         return (NULL);
//     if (negative)
//         itoa[0] = '-';
//     itoa[count_dgts--] = '\0';
//     while (n > 0)
//     {
//         itoa[count_dgts--] = (char)((n % 10) + 48);
//         n = (n - (n % 10)) / 10;
//     }
//     return (itoa);
// }

// void    ft_putnbr_fd(int n, int fd)
// {
//     char    *buf;

//     buf =  ft_itoa(n);
//     write(fd, buf, ft_strlen(buf));
// }
