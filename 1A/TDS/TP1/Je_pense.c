#include <stdio.h>
#include <stdlib.h>
float n;
int tentatives=0,nombre;
int main()
{
    srand(time(NULL));
    nombre=(int)(5.*rand()/RAND_MAX)+1;
    printf("%d\n",nombre);
    do
    {
        printf("Entrez le nombre entre 1 et 5 inclus auquel je pense\n");
        scanf("%f",&n);
        tentatives+=1;
        if (n==nombre)
        {
            printf("Gagne!");
            break;
        }
        if (tentatives==3)
        {
            printf("Dommage!");
            break;
        }
    }

    while(n!=nombre);
    printf("%d tentatives\n",tentatives);

    return 0;
}
