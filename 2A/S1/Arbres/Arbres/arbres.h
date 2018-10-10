#ifndef ARBRES_H
#define ARBRES_H

typedef struct sListNode
{
	treeNode * m_node;
	struct sListNode * m_next;
}listNode;

typedef struct sTreeNode
{
	int m_data;
	listNode * m_children;
}treeNode;



#endif 
