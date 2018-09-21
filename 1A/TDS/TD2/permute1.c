#include <stdio.h>
int main()
{
	int a=2,b=4,tmp;
    printf("Avant\na=%d\nb=%d\n",a,b);
    tmp=a;
    a=b;
    b=tmp;
    printf("\nApres\na=%d\nb=%d\n",a,b);
    return 0;
}
