#include <stdio.h>
#include <math.h>
void solveur(float a, float b, float c)
{
    float D;
    float x,y;
    D=(b*b)-(4*a*c);    
    if (D<0)
        printf("Pas de solutions reeles\n");
    if (D==0)
        printf("X0=%.3f\nX0=(-%.2f)/(2*%.2f)",(-b/(2*a)),b,a);

    if (D>0)
    {
        x=(-b-sqrt(D))/(2*a);
        y=(-b+sqrt(D))/(2*a);
        printf("X1=%.3f\nX2=%.3f\nX1=(-%.2f-sqrt(%.2f))/(2*%.2f)\nX2=(-%.2f-sqrt(%.2f))/(2*%.2f)\n",x,y,b,D,a,b,D,a);
    }
}

int main()
{
    int a,b,c;
    printf("Entrez A,B et C pour résoudre votre equation du type Ax²+Bx+C=0\n");
    scanf("%d",&a);
    scanf("%d",&b);
    scanf("%d",&c);
    solveur(a,b,c);	
    return 0;


}
