#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float n;
int tentatives=0,nombre;
int main()
{
    nombre=(int)(rand()%(50000 + 1 - 10000)+10000);
    printf("%d\n",nombre);
    printf("Trouvez le nombre entre 10'000 et 50'000 ! Vous avez 45 secondes\n");
    time_t secondes1,secondes2;
    secondes1=time(NULL);
    do
    {

        scanf("%f",&n);
        tentatives+=1;
        if (n==nombre)
        {
            printf("Gagne!");
            break;
        }
        if (n>nombre)
        {
            printf("-\n");
        }
        if (n<nombre)
        {
            printf("+\n");
        }
        secondes2=time(NULL);

    } while(n!=nombre && secondes2-secondes1<45);



    printf("%d tentatives\n",tentatives);

    return 0;
}
