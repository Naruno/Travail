#pragma once
#include "piles.h"
#include <stdio.h>
void push(node** p_head, node* p_new) {

	if (!(p_head) || !p_new) {
		return;
	}
	p_new->m_next = (*p_head);
	*p_head = p_new;
}

node* pop_stack(node** p_head) {
	
	if (!p_head) {
		return;
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

void test_stack() {

	node* maListe = createListNode(1);
	node* new = createListNode(0);

	printf("On creer la pile : ");
	printList_int(maListe);

	printf("On ajoute un element : ");
	push(&maListe, new);
	printList_int(maListe);

	printf("On enleve un element : ");
	node* suppr = pop_stack(&maListe);	
	printList_int(maListe);

	printf("On enleve un element : ");
	suppr = pop_stack(&maListe);
	printList_int(maListe);

	printf("On ajoute un element : ");
	push(&maListe, new);
	printList_int(maListe);

	printf("On libere la pile : ");
	free_stack(&maListe);
	printList_int(maListe);
}