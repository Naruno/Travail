#include <stdio.h>
#include <stdlib.h>
int main()
{
	float n;
	int tentatives=0,nombre;
    srand(time(NULL));
    nombre=(int)(100.*rand()/RAND_MAX);
    printf("%d\n",nombre);
    do
    {
        printf("Entrez le nombre entre 1 et 100 inclus auquel je pense\n");
        scanf("%f",&n);
        tentatives+=1;
    }while(n!=nombre);
    printf("%d tentatives\n",tentatives);
    return 0;
}
