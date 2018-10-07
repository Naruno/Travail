#pragma once
typedef struct node node;
struct node {

	void* m_data;
	node* m_next;
};

node* createListNode(void* p_value);
void freeList(node * p_pRoot);

node* addFirst(node* p_pRoot, void* p_value);
node* addLast(node* p_pRoot, void* p_value);

node* addSortAsc(node* p_node, void* p_value);
void addSortAsco(node** p_node, void* p_value);
node* addSortDesc(node* p_node, void* p_value);

node* pop(node* p_pRoot, void** p_result); 
node* popLast(node* p_node);

int listLength(node * p_pRoot);
void printList_int(node* p_pRoot);
void printList_str(node* p_pRoot);
node* at(node * p_pRoot, int p_index);

void Hanoi(int n, node* D, node* A, node* I);

void Test_List();