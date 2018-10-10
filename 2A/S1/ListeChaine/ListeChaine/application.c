#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "liste.h"
#include "piles.h"
#include "application.h"

int calculatrice_polonaise(char* p_calcul) {

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
			push(&pile, createListNode(nombre));
			
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
	int resultat = calculatrice_polonaise(calcul);

	printf("Le resultat de (%s) est %d\n", calcul, resultat);
}

int calculatrice_infixe() {
	node* pile_operandes = createListNode(0);
	node* pile_operateurs = createListNode('+');
	node *dernier, *avant_dernier;
	char calcul[255], operateur = 'a';
	int taille = 0, i = 0, nombre = 0, construction = 0;
	int compteur_p_ouvrante = 0, compteur_p_fermante = 0, compteur_operateurs = 0;
	pop_stack(&pile_operandes);
	pop_stack(&pile_operateurs);
	printf("Bienvenu dans la calculatrice !\nEntrez une expression a calculer\nCalcul : ");
	scanf("%[^\n]", calcul);
	taille = strlen(calcul);	

	for (i = 0; i < taille + 4; i++) {
		if (calcul[i] == '(') {
			compteur_p_ouvrante++;
		}
		if (calcul[i] == ')') {
			compteur_p_fermante++;
		}
		if (calcul[i] == '+' || calcul[i] == '-' || calcul[i] == 'x' || calcul[i] == '/') {
			compteur_operateurs++;
		}
	}
	if ((compteur_p_ouvrante != compteur_p_fermante) || (compteur_operateurs != compteur_p_fermante)) {
		printf("Veuillez entrer une expression correctement parethesee !\n");
		return 0;
	}/*
	if ((calcul[0] != '(' || calcul[2] != '(' || calcul[taille - 1] != ')' || calcul[taille - 3] != ')')) {	

		calcul[0] = '(';
		calcul[1] = ' ';
		
		for (i = taille + 1; i > 1; i--) {
			calcul[i] = calcul[i - 2];
		}
			
		calcul[taille + 2] = ' ';
		calcul[taille + 3] = ')';
		calcul[taille + 4] = '\0';		
	}
	printf("calcul : _%s_\n", calcul);
	*/

	for (i = 0; i < taille + 4; i++) {

		if (calcul[i] == '(') {
			continue;
		}
		if (calcul[i] >= 48 && calcul[i] <= 57) {

			nombre = nombre * 10 + calcul[i] - '0';
			construction = 1;
			continue;
		}
		if (calcul[i] == ' ' && construction) {			
			push(&pile_operandes, createListNode(nombre));

			nombre = 0;
			construction = 0;
			continue;
		}
		switch (calcul[i]) {

		case '+':
			push(&pile_operateurs, createListNode('+'));			
			break;

		case '-':
			push(&pile_operateurs, createListNode('-'));
			break;

		case 'x':
			push(&pile_operateurs, createListNode('x'));
			break;

		case '/':
			push(&pile_operateurs, createListNode('/'));
			break;

		default:
			break;
		}
		if (calcul[i] == ')' && pile_operandes != NULL && pile_operandes != NULL) {
			dernier = pop_stack(&pile_operandes);
			avant_dernier = pop_stack(&pile_operandes);
			operateur = pop_stack(&pile_operateurs)->m_data;

			switch (operateur)
			{

			case '+':
				push(&pile_operandes, createListNode((int)avant_dernier->m_data + (int)dernier->m_data));
				break;

			case '-':
				push(&pile_operandes, createListNode((int)avant_dernier->m_data - (int)dernier->m_data));
				break;

			case 'x':
				push(&pile_operandes, createListNode((int)avant_dernier->m_data * (int)dernier->m_data));
				break;

			case '/':
				push(&pile_operandes, createListNode((int)avant_dernier->m_data / (int)dernier->m_data));
				break;
			default:
				break;
			}
		}
	}
	nombre = pile_operandes->m_data;
	free_stack(&dernier);
	free_stack(&avant_dernier);
	free_stack(&pile_operandes);
	free_stack(&pile_operateurs);
	return nombre;
}