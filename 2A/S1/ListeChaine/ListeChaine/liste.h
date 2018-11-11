#ifndef LISTE_H	
#define LISTE_H

#pragma once
typedef struct node node;
struct node {

	int type;
	void* m_data;
	node* m_next;
};

node* createListNode(void* p_value, int type);
void freeList(node * p_pRoot);

node* addFirst(node* p_pRoot, void* p_value, int type);
node* addLast(node* p_pRoot, void* p_value, int type);

node* addSortAsc(node* p_node, void* p_value, int type);
void addSortAsco(node** p_node, void* p_value, int type);
node* addSortDesc(node* p_node, void* p_value, int type);

node* pop(node* p_pRoot, void** p_result); 
node* popLast(node* p_node);

int listLength(node * p_pRoot);
void printList(node* p_pRoot);
node* at(node * p_pRoot, int p_index);

void Hanoi(int n, node* D, node* A, node* I);

void test_Liste();
#endif