#ifndef HUFFMAN
#define HUFFMAN

#include <stdio.h>
#include <stdlib.h>

int compression(char* p_path);

typedef struct node node;
typedef struct tree tree;
struct node {

	char m_nb_occurence;
	tree*  m_tree;
	node* m_next;
};

struct tree {

	char m_data;	
	tree* m_left;
	tree* m_right;
};



node* createListNode(char p_value, char p_nombre);
tree * creerNoeudArbre(char p_value);
void addSortAsco(node** p_node, char p_value, char p_nombre);
void printList(node* p_pRoot);
void freeList(node * p_pRoot);
void libererArbre(tree ** p_ppRoot);
#endif
