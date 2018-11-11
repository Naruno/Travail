#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"
#include "piles.h"

void push(node** p_head, node* p_new) {

	if (!(p_head) || !p_new) {
		return;
	}
	p_new->m_next = (*p_head);
	*p_head = p_new;
}

node* pop_stack(node** p_head) {
	
	if (!p_head) {
		return NULL;;
	}
	node* tmp = *p_head;	
	*p_head = (*p_head)->m_next;
	tmp->m_next = NULL;
	return tmp;
}

void free_stack(node** p_head) {

	if (!(*p_head)) {
		return;
	}
	free_stack(&(*p_head)->m_next);
	free(*p_head);
	*p_head = NULL;
	return;
}

void test_Pile() {

	node* maListe = createListNode(1, 1);
	node* new = createListNode(0, 1);

	print("On créer la pile : ");
	printList(maListe);

	print("On ajoute un élement : ");
	push(&maListe, new);
	printList(maListe);

	print("On enlève un élement : ");
	node* suppr = pop_stack(&maListe);	
	printList(maListe);

	print("On enlève un élement : ");
	suppr = pop_stack(&maListe);
	printList(maListe);

	print("On ajoute un élement : ");
	push(&maListe, new);
	printList(maListe);

	printf("On libere la pile : ");
	free_stack(&maListe);
	printList(maListe);
}