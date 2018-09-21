#include <stdio.h>
int rang;
float i,somme=0;
int main()
{
    printf("Rang n de la serie? :");
    scanf("%d",&rang);
    for(i=1;i-1<rang;i+=1)
        somme+=(1/i);
    printf("%.6f\n",somme);
    return 0;
}
