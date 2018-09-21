#ifndef VECTEURS
#define VECTEURS
#include "vecteur.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils_SDL.h"

int Arrondit(const float x)
{
	if (0 <= x)
		return floor(x + (float)0.5);
	else
		return ceil(x - (float)0.5);
}

point vect_normal(point u) {

	point v;
	int inter = 1*(1 + ( pow(u.m_x, 2) / pow(u.m_y, 2) ));
	inter = Arrondit(inter);
	printf("Inter = %d\n", inter);
	if (!u.m_y) {
		printf("Division par zero\n");
		exit(0);
	}	

	v.m_x = Arrondit(-sqrt(inter ) / (inter));
	v.m_y = -v.m_x;

	return v;
}

point vect_somme(point u, point v) {

	point x;
	x.m_x = u.m_x + v.m_x;
	x.m_y = u.m_y + v.m_y;

	return x;
}

point vect_scal(float a, point v) {

	point x;
	x.m_x = a * v.m_x;
	x.m_y = a * v.m_y;

	return x;
}


void vect_affiche(point u) {

	printf("Coordonnes :\nx = %d\ny = %d\n", u.m_x, u.m_y);
}

point nouveau_vect(point u, point v) {

	float distance;
	float hauteur;
	point milieu;
	point v_directeur;
	point v_normal;
	point transition;
	point sommet;

	milieu.m_x = (u.m_x + v.m_x) / 2;
	milieu.m_y = (u.m_y + v.m_y) / 2;
	printf(" Milieu\n");
	vect_affiche(milieu);

	v_directeur.m_x = (v.m_x - u.m_x);
	v_directeur.m_y = (v.m_y - u.m_y);
	printf(" v_directeur\n");
	vect_affiche(v_directeur);

	v_normal = vect_normal(v_directeur);
	printf(" v_normal\n");	

	vect_affiche(v_normal);

	distance = sqrt(pow(v.m_x - u.m_x, 2) + pow(v.m_y - u.m_y, 2));
	printf(" distance : %f\n", distance);

	hauteur = Arrondit((sqrt(3) / 2) * distance);
	printf(" hauteur : %f\n", hauteur);

	transition = vect_scal(hauteur, v_normal);
	printf(" transition\n");
	vect_affiche(transition);
	
	sommet = vect_somme(v_normal, milieu);
	printf(" sommet\n");
	vect_affiche(sommet);

	return sommet;
}

void decoupage(point a, point b, point *p1, point *p2) {
	printf("A \n");
	vect_affiche(a);
	printf("B \n");
	vect_affiche(b);
	int x = (a.m_x + b.m_x) / 3;
	int y = (a.m_y + b.m_y) / 3;

	printf("P1\n");
	p1->m_x = x;
	p1->m_y = y;
	vect_affiche(*p1);
	
	printf("P2\n");
	p2->m_x = 2 * x;
	p2->m_y = 2 * y;
	vect_affiche(*p2);
}

void tracer(SDL_Surface * p_affichage, point p_a, point p_b) {

	_SDL_DrawLine(p_affichage, p_a.m_x, p_a.m_y, p_b.m_x, p_b.m_y, 200, 50, 5);
}
#endif