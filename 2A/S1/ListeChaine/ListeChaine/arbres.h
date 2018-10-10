#pragma once
#ifndef ARBRES_H
#define ARBRES_H

typedef struct sTreeNode treeNode;
typedef struct sListNode listNode;

struct sTreeNode
{
	int m_data;
	listNode * m_children;
};
struct sListNode
{
	treeNode * m_node;
	listNode * m_next;
};


#endif
