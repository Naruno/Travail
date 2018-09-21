#include <stdio.h>

float square(int c,int a, float n)
{
    float U=(float)c;
    while (U-((0.5)*(U+(a/U)))>n)
        U=(0.5)*(U+(a/U));
    return U;
}
int main()
{
    int a,c;
    float n;
    printf("Quelle racine voulez vous approximer?\nQuelle Precision?\nUo=?\n");
    scanf("%d",&a);
    scanf("%f",&n);

    scanf("%d",&c);
    printf("%.5f\n",square(c,a,n));
}
