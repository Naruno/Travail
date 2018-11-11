#ifndef PILE_H
#define PILE_H
#pragma once
#include "liste.h"
// Ajoute un élément à une pile. C'est à dire en tête.
void push(node** p_head, node* p_new);
node * pop_stack(node** p_head);
void free_stack(node** p_head);

void test_Pile();
#endif