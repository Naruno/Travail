#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main()
{
    int usleep(useconds_t usec);
    int i;
    int nombre;
    srand(time(NULL));
    while (1)
    {
        usleep(5000);
        for(i=0;i<60;i++)
        {
            nombre=rand();
            if(nombre%2==0)
                printf(" ");
            else
                printf("*");
        }
        printf("\n");
    }
}
