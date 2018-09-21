#include <stdio.h>
int addition(int a,int b)
{    
    return a+=b;
}
int main()
{
    int a,b;
    printf("Entrez deux nombres dont vous voulez la somme :\n");
    scanf("%d",&a);
    scanf("%d",&b);
    printf("%d+%d=%d\n",a,b,addition(a,b));
    return 0;
}
