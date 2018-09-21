#include <stdio.h>
int main()
{
    int a=1,b=2;
    printf("Avant\na=%d\nb=%d\n",a,b);
    a^=b,b^=a,a^=b;
    printf("\nApres\na=%d\nb=%d\n",a,b);
    return 0;
}
