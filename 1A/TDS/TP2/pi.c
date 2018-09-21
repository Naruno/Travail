#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
float TirageAleatoire(float N)
{
    return N*(rand()/(double)RAND_MAX);
}
int EstInscrit (float N)
{
    float d,Px,Py;
    Px=TirageAleatoire(N);
    Py=TirageAleatoire(N);
    //printf("%f\n%f\n",Px,Py);
    d=sqrt(pow(Px-(N*0.5),2)+pow(Py-(N*0.5),2));
    if (d<N*0.5)
        return 1;
    else
        return 0;
}
int main()
{
    float N,Oui=0,Non=0;
    int T;
    srand(42);
    printf("Cote N du carre =? : ");
    scanf("%f",&N);
    printf("Faire le test combien de fois ?");
    scanf("%d",&T);
    for(int i=1;i<T;i++)
    {
        if (EstInscrit(N)==1)
            Oui++;
        else
            Non++;
    }
    printf("PI ~ %f\n",(Oui/T)*4);
    return 0;
}