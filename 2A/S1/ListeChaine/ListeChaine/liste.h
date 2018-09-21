#pragma once
typedef struct sNode {

	int m_data;
	struct sNode* m_next;
	
}Node;

Node * ajoutTri(Node * p_head, Node * p_node);