#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "liste.h"
#include "piles.h"
#include "application.h"

int calculatrice(char* p_calcul) {

	int taille = strlen(p_calcul), i = 0, nombre = 0, construction = 0;
	node* pile = createListNode(0);
	node *new, *dernier, *avant_dernier;
	pop_stack(&pile);
	
	for (i = 0; i < taille; i++) {		
		if (p_calcul[i] >= 48 && p_calcul[i] <= 57) {
			
			nombre = nombre * 10 + p_calcul[i] - '0';			
			construction = 1;
			continue;
		}
		if (p_calcul[i] == ' ' && construction) {
			new = createListNode(nombre);
			push(&pile, new);
			
			nombre = 0;
			construction = 0;
			continue;
		}			
		switch (p_calcul[i]){

		case '+':	
			dernier = pop_stack(&pile);
			avant_dernier = pop_stack(&pile);
			new = createListNode((int)avant_dernier->m_data + (int)dernier->m_data);				
			push(&pile, new);					
			break;
		
		case '-':
			dernier = pop_stack(&pile);
			avant_dernier = pop_stack(&pile);
			new = createListNode((int)avant_dernier->m_data - (int)dernier->m_data);			
			push(&pile, new);			
			break;

		case 'x':
			dernier = pop_stack(&pile);
			avant_dernier = pop_stack(&pile);
			new = createListNode((int)avant_dernier->m_data * (int)dernier->m_data);		
			push(&pile, new);					
			break;

		case '/':
			dernier = pop_stack(&pile);
			avant_dernier = pop_stack(&pile);
			new = createListNode((int)avant_dernier->m_data / (int)dernier->m_data);		
			push(&pile, new);						
			break;

		default:			
			break;
		}
	}	
	return pile->m_data;
}

void Test_Calculatrice() {
	char* calcul = "4 5 + 3 10 5 / - x";
	int resultat = calculatrice(calcul);

	printf("Le resultat de (%s) est %d\n", calcul, resultat);
}