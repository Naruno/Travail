#pragma once
#include "liste.h"
#include "piles.h"
#include "application.h"
#include "arbres.h"

int main(){
	
	int res = calculatrice_infixe();
	printf("Resultat : %d\n", res);
	system("pause");
	return 0;
}