#pragma once
typedef struct sNode {

	int m_data;
	struct sNode* m_next;
	
}Node;
Node * ajoutTri(Node * p_head, Node * p_node);



typedef struct Liste Liste;
struct Liste
{
	Element *premier;
};

typedef struct Element Element;
struct Element
{
	int nombre;
	Element *suivant;
};

Element initialisation(int nombre);
