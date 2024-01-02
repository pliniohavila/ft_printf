#include <stdio.h>
#include <string.h>

int main(void) 
{
   char     str[2];

   str[0] = 'O';
   str[1] = 'l';
   str[2] = 'a';
   str[3] = '\0';
   printf("%s\n", str);
   return (0);
}