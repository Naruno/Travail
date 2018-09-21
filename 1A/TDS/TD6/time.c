#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(){
	int a=1,b=1,c,d;
	printf("Entrez un chiffre\n");
	scanf("%d",&a);
	c=time(NULL);
	while(b!=0){
		printf("Entrez un autre chiffre\n");
		scanf("%d",&b);
		d=time(NULL);	
	}
	printf("Temps écoulé : %ds\n",d-c);
	return 0;
}