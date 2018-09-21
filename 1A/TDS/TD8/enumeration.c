#include <stdio.h>

typedef enum JourSemaine{
	
	DIMANCHE,
	LUNDI,
	MARDI,
	MERCREDI,
	JEUDI,
	VENDREDI,
	SAMEDI,

}Jsemaine;

void AfficheJour(Jsemaine jour){
	
	printf("%d\n",jour);		
}

int main(){
	Jsemaine aujourdhui;
	aujourdhui=DIMANCHE;
	AfficheJour(aujourdhui);
	return 0;
}