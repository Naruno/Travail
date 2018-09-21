#include <stdio.h>

int parite(int nombre){	
	if ((nombre &1)==0)
		return 0;
	else
		return 1;	
}

int mult(int n,int p){ //multiplie n par 2^p	
	return n<<p;
}

int div(int n,int p){ //divise n par 2^p
	return n>>p;
}

void base_deux(int n){	
	for(int i=14;i>=0;i--)
		printf("%d",(n>>i)&1);
	printf("\n");	
}

void nb_bits(int n){
	int compteur=0;
	for(int i=14;i>=0;i--){
		if((n>>i)&1)
			compteur++;
	}		
	printf("%d\n",compteur);	
}

void b2_b8(int n){
	
	//faire des groupes de 3 bits 
}

int main(){	
	printf("%d\n%d\n",parite(15),parite(24));	
	printf("%d\n%d\n",mult(3,3),mult(2,3));	
	printf("%d\n%d\n\n",div(4,1),div(33,3));	
	base_deux(90);
	nb_bits(90);

	return 0;
}