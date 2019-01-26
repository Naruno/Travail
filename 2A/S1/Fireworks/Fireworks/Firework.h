#pragma once
#ifndef FIREWORK
#define FIREWORK
#include "vector.h"

#define RAND(MIN, MAX) (rand() / (float)(RAND_MAX+1) * (MAX - MIN) + MIN)

typedef struct Particule_s Particule;
typedef struct Firework_s Firework;

struct Firework_s {
	double position[3]; // Between -2.5 and 2.5 for X/Z, 0 for Y.
	int nb_level; // Entre 2 et 3.
	Particule* p_particule; // Adress of the first particule created at the same time of the firework.
};

struct Particule_s {
	double position[3]; // Between -2.5 and 2.5 for X/Z, 0 for Y.
	double speed[3]; // Random direction, norm = 6.
	double size; // Between 0.02 and 0.05.
	double lifetime; // Between 3 and 5.
	unsigned char color[3]; // Between 128 ans 255 for each color.
	char children; // 0 if no child, 1 esle.
	
	Particule* p_father;
	Particule* p_brother;
	Particule* p_children;
};

enum coordinates {
	X,
	Y,
	Z,
	NB_COORDS
};

enum colors {
	RED,
	GREEN,
	BLUE,
	NB_COLORS
};

void create_Firework(Firework* root);

Particule* create_Particule(double pos[3]);

Particule* create_child(Particule* parent);

void update_Firework(Particule** particule, double dt, int nb_Niveaux, int nb_MAX);
#endif