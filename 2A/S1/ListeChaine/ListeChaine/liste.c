#pragma once
#include "liste.h"

Node * ajoutTri(Node * p_head, Node * p_node) {
	
	if (!p_node) {
		return p_head;
	}
	if (!p_head || p_node->m_data < p_head->m_data) {
		p_node->m_next = p_head;
		return p_node;
	}
	p_head->m_next = ajoutTri(p_head->m_next, p_node);
}

Element initialisation(int nombre) {

	Element 
}