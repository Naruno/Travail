#include <stdio.h>

void swap(int a, int b)
{
    a^=b,b^=a,a^=b;
}
int main()
{
    int a=5,b=10;
    printf("a=%d\nb=%d\n",a,b);
    swap(a,b);
    printf("a=%d\nb=%d\n",a,b);
	return 0;
}
//On remarque que la valeur de a et b reste inchangée
//La modification de a et b n'existe que dans la fonction swap
