#include <stdio.h>
#include <math.h>
long int miroir(long int nombre)
{
	long int miroir=0;
	while(nombre>0){
		miroir=miroir*10+nombre%10;
		nombre/=10;
	}	    
    return miroir;
}
int NbDigit(long int nombre)
{
    int chiffre=0;
    while(nombre>0){
        nombre/=10;
        chiffre++;
	}
    return chiffre;
}
int Reconnaitre_palindrome(long int N)
{	
	if(NbDigit(N)%2==0){	
		if(miroir(N/(pow(10,NbDigit(N)/2)))==N%(int)(pow(10,(NbDigit(N)/2))))					
			return 1;			
		else return 0;	
	}
	else{
		if(miroir(N/(pow(10,(NbDigit(N)+1)/2)))==N%(int)(pow(10,((NbDigit(N)+1)/2)-1)))
			return 1;
		else return 0;			
	}	
}
int palindrome(long int nombre,int *c)
{
	int count=0,countn=*c;	
	while(Reconnaitre_palindrome(nombre)!=1){	
		if(nombre>922337203685477580){
			nombre=0;			
			countn++,*c=countn;
			printf("Trop Long : %d\n",*c);
			return count;
		}
		nombre+=miroir(nombre);		
		count++;
	}	
	printf("%ld\n",nombre);
	if(count>25)
		count=0;
	return count;	
}
int main()
{	
	int countf=0,countn=0,*p_countn=&countn;
	for(int i=100;i<1000;i++){
		printf("%d : ",i);
		countf+=palindrome(i,&countn);		
	}	
	printf("\n%d itterations pour tout les nombres de 100 a 999\nMoyenne : %f iteration par nombre\n",countf,(float)countf/(900-*p_countn));	
	return 0;
}