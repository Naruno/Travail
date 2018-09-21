#include <stdio.h>
#include <math.h>

int f(int a,float *b, char c)
{
	b=(float *)&a;	
	return (int *)b;
}

void Puissance_pointeur(int *p_a, int n)
{
	int p=*p_a;
	for(int i=1;i<n;i++)		
		(*p_a)*=p;
}

void Echange(char *a,char *b)
{	
	if(a==NULL || b==NULL)
		return;
	char c=*b;
	*b=*a;
	*a=c;
	printf("Pendant\nc1=%c\nc2=%c\n",*a,*b);
}

int main()
{
	char c1='r',c2='k',c='r',*r=&c1,*k=&c2,*o=NULL;
	int a=4,n=3,*p_a=&a;
	float *b=NULL;
	
	printf("A l adresse %p il y a %d\n",(void *)f(a,b,c),a);	
	Puissance_pointeur(p_a,n);
	printf("%d\n",a);
	printf("Avant\nc1=%c\nc2=%c\n",*r,*k);
	
	Echange(r,k);
	printf("Apres\nc1=%c\nc2=%c\n",*r,*k);	
	Echange(r,o);
	return 0;

}
