#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
   char     *buffer;
   
   buffer = malloc(1024);
   sprintf(buffer, "%s", argv[1]);
   printf("%s\n", buffer);
   return (0);
}