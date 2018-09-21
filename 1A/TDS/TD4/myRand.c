#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int my_rand(int a,int b)
{
    int nombre;
    srand(time(NULL));
    nombre=(int)(rand()%(b+1-a)+a);
    return nombre;
}
int main(int argc,char **argv)// ./myRand.exe a b 
{
    printf("%d\n",my_rand(atoi(argv[1]),atoi(argv[2])));
	return 0;
}
