#include <stdio.h>
#include <stdlib.h>

typedef struct Etudiant_s{
	char nom[20];
	char prenom[20];
	int numero;
	int moyenne;
}Etudiant;

int main(){
	Etudiant variable;
	Etudiant *pointeur=&variable;
	pointeur->moyenne=7;
	
	printf("%d\n",variable.moyenne);
	
	int tableau[10];
	
	for(int i=0;i<10;i++)
		tableau[i]=variable.moyenne;
	
	for(int i=0;i<10;i++)
		printf("[%d]",tableau[i]);
		
	printf("\n");	
	
	int *tabdyn=(int*)calloc(1,sizeof(int));
	
	for (int i=0;i<10;i++)
		tabdyn[i]=variable.moyenne;
		
	for (int i=0;i<10;i++)
		printf("[%d]",tabdyn[i]);				
		
	printf("\n");	
    
	return 0;
}