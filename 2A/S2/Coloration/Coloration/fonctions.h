#ifndef FONCTIONS_H
#define FONCTIONS_H
#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct graphe_s Graphe;
typedef struct degsommet_s Degsommet;

struct graphe_s {
	int N;
	int** tableau;
};

struct degsommet_s {
	char deg;
	char num;
	char color;
};


Graphe* creerGraphe(int p_N);

Graphe* lireFichier(FILE* p_file);

Degsommet* degretrie(Graphe* p_graphe);

char ToutColor(Degsommet* p_tab, int p_taille);

void Colorer(Degsommet* p_tab, int p_taille, Graphe* p_graphe);

int degAssocie(Degsommet *p_tab, int taille, int indice);
#endif // !FONCTIONS_H