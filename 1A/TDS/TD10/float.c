#include <stdio.h>

typedef union ieee754_float{
	float f;
	struct{
		unsigned int mantisa : 23;
		unsigned int exponent : 8;
		unsigned int sign : 1;
	};

}float_cast;

void Printb(int n,int nb_bits){		
	for(int i=nb_bits-1;i>=0;i--)
		printf("%d",(n>>i)&1);
	printf("\n");	
}

void Print_ieee(int n,float_cast norme){
	Printb(n,23);
	n=n>>23;
	
	Printb(n,8);
	n=n>>8;
	
	Printb(n,1);	
}

int main(){
	float_cast norme;
	Print_ieee(22,norme);

	
	
	return 0;
}

/*int n=25;
	Printb(n,5);
	n=n>>2;
	Printb(n,5);

	*/