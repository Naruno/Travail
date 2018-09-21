#include <stdio.h>
#include <math.h>
int Ajoute(int n){	
	int a=n,b=0;
	
	while(a!=0){		
		a/=10;
		b++;
	}
	printf("%d\n\n",b);
	int tab[b];
	for(int i=0;i<b;i++){		
		tab[i]=(n%10)+1;
		if (tab[i]==10)
			tab[i]=0;
		n/=10;	
		printf("%d\n",tab[i]);	
		a+=tab[i]*pow(10,i);
	}
	return a;
}

int main()
{
	printf("%d\n",Ajoute(6397));	
	return 0;
}
