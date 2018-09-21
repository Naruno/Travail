#include <stdio.h>
//ON CONSIDERE DANS CE PROGRAMME QUE QUAND ON PAYE A LA CAISSE, ON NE DONNE PAS MOINS QUE LE MONTANT DEMANDE, TOUJOURS UN PEU PLUS
int main()
{
    float r,montant=18.75,a;
    int c1=0,c2=0,c3=0,c4=0,c5=0,c6=0;
    printf("Montant a payer: %.2f euros\nVous donnez:",montant);
    scanf("%f",&a);
    a-=montant;
    r=a;
    while(a-1>0)
    {
        a-=1;
        c1++;
    }
    while(a-0.5>0)
    {
        a-=0.5;
        c2++;
    }
    while(a-0.2>0)
    {
        a-=0.2;
        c3++;
    }
    while(a-0.1>0)
    {
        a-=0.1;
        c4++;
    }
    while(a-0.02>0)
    {
        a-=0.02;
        c5++;
    }
    while(a-0.01>0)
    {
        a-=1;
        c6++;
    }
    printf("Rendu:%.2f€ :%dx1€,%dx50cents,%dx20cents,%dx10cents,%dx2cents,%dx1cents\n",r,c1,c2,c3,c4,c5,c6);
    return 0;
}
