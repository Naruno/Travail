#include <stdio.h>
float montant=18.75,argent;

int main()
{
	printf("Montant a payer: %.2f euros\nVous donnez:",montant);
    scanf("%f",&argent);
    argent-=montant;
    printf("Rendu :%.2f€\n",argent);
	return 0;
}
