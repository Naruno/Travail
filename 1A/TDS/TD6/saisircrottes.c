#include <stdio.h>
#include <stdlib.h>
int SaisirCrottes(int Tab[],int n){
	float somme=0;
	int crottes,indice=0;
	while(indice<n){
		printf("Crottes a l'heure %d : ",indice+1);
		scanf("%d",&crottes);
		if (crottes<0)
			break;
		Tab[indice]=crottes;
		indice++;
	}	
	for(int i=0;i<n;i++){		
		somme+=Tab[i];				
	}
	printf("Moyenne : %.3f\n",somme/indice);
	return indice;
}	
int main()
{
	int tab[168]={0};
	system("clear");
	SaisirCrottes(tab,168);	
	return 0;
}