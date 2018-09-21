#include "utils_SDL.h"
typedef struct sPoint {
	int m_x;
	int m_y;
}point;

point vect_normal(point u);
point vect_somme(point u, point v);
void vect_affiche(point u);
point nouveau_vect(point u, point v);
void decoupage(point a, point b, point *p1, point *p2);
void tracer(SDL_Surface * p_affichage, point p_a, point p_b);