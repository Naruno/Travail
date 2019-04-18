#include "Huffman.h"

int compression(char* p_path) {
	printf("[%s]\n", p_path);
	FILE* file = NULL;
	node* liste = NULL;
	int tab[256] = { 0 }, count = 0, i;
	unsigned char c;
	fopen_s(&file, p_path, "rb");
	if (!file) {
		return 0;
	}
	while (fread(&c, sizeof(char), 1, file)) {
		tab[c]++;
		count++;
	}

	for (i = 0; i < 256; i++) {
	
		if (!tab[i])
			continue;
		addSortAsco(&liste, i, tab[i]);
		
	}
	printf("N = %d\n", count);
	printList(liste);
	freeList(liste);
	fclose(file);
	return 1;
}

node* createListNode(char p_value, char p_nombre) {
	node* noeud = (node*)calloc(1, sizeof(*noeud));

	if (!noeud) {
		printf("Erreur lors de l'allocation de list ou node.\n");
		exit(EXIT_FAILURE);
	}
	//noeud->m_data = p_value;
	noeud->m_tree = creerNoeudArbre(p_value);
	noeud->m_nb_occurence = p_nombre;
	noeud->m_next = NULL;
	return noeud;
}

tree * creerNoeudArbre(char p_value) {

	tree* noeud = (tree*)calloc(1, sizeof(*noeud));

	if (!noeud) {
		printf("Erreur lors de l'allocation de list ou node.\n");
		return NULL;
	}	
	noeud->m_data = p_value;
	noeud->m_left = NULL;
	noeud->m_right = NULL;

	return noeud;
}

void addSortAsco(node** p_node, char p_value, char p_nombre) {
	// Cette fonction insere un node en respectant l'ordre du membre m_data en utilisant un passage par adresse.

	if (!p_node)
		return;

	if (!*p_node || p_nombre <= (*p_node)->m_nb_occurence ) {

		node* nouveau = createListNode(p_value, p_nombre);
		nouveau->m_next = *p_node;
		*p_node = nouveau;
		return;
	}
	else {
		addSortAsco(&((*p_node)->m_next), p_value, p_nombre);
		return;
	}
}

void printList(node* p_pRoot) {
	// Cette fonction affiche une liste.
	if (!p_pRoot) {
		printf("NULL\n");
		return;
	}	
	printf("[%c | %d] -> ", p_pRoot->m_tree->m_data , p_pRoot->m_nb_occurence);
	printList(p_pRoot->m_next);
}

void freeList(node * p_pRoot) {

	if (!p_pRoot) {
		return;
	}
	libererArbre(&(p_pRoot->m_tree));
	freeList(p_pRoot->m_next);	
	free(p_pRoot);
}

void libererArbre(tree ** p_ppRoot) {

	if (!(*p_ppRoot)) {
		return;
	}
	libererArbre(&((*p_ppRoot)->m_left));
	libererArbre(&((*p_ppRoot)->m_right));
	free(*p_ppRoot);
	*p_ppRoot = NULL;
	return;
}