#include <stdio.h>
int main()
{
	int a=2,b=4,c=5,tmp;
    printf("Avant\na=%d\nb=%d\nc=%d\n",a,b,c);
    tmp=c;
    c=b;
    b=a;
    a=tmp;
    printf("\nApres\na=%d\nb=%d\nc=%d\n",a,b,c);
    return 0;
}
