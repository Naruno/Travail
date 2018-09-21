#include <stdio.h>
#include <stdlib.h>
unsigned long long int miroir(unsigned long long int nombre)
{
	unsigned long long int miroir=0,*p_miroir=&miroir;
	while(nombre>0){
		*p_miroir=*p_miroir*10+nombre%10;
		nombre/=10;
	}
	return miroir;
}
int palindrome(unsigned long long int nombre,int *c,int *ci)
{
	int count=0,countn=*c;	
	while(nombre!=miroir(nombre)){	
		if(nombre>184467440737095516){
			nombre=0;			
			count=0,countn++,*c=countn;
			printf("|NULL|\n");
			return count;
		}
		nombre+=miroir(nombre);		
		count++;		
	}	
	printf("%llu\t|%d|\n",nombre,count);
	if(count>*ci)
		*ci=count;
	return count;	
}
int main()
{		
	int countf=0,countn=0,countinter=0,i,n,a;	
	while(n<=i || i<0){
		system("clear");
		printf("Partir de ? jusqu a ?\n");	
		scanf("%d",&i);
		scanf("%d",&n);
	}	
	a=i;
	while(i<=n){	
		printf("%d\t",i);
		countf+=palindrome(i,&countn,&countinter);
		i++;
	}
	printf("\n%d itterations pour tout les nombres de %d a %d\nMoyenne : %f iteration par nombre\n%d exeptions\nRecord : %d iterations\n",countf,a,n,(float)countf/(n-a-countn),countn,countinter);	
	return 0;
}