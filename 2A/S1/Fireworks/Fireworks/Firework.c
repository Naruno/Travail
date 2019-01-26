#include "Firework.h"
#include <stdlib.h>
#include <math.h>

#define PI 3.141592

void create_Firework(Firework* root)
{	
	root->position[X] = RAND(-2.5, 2.5);
	root->position[Y] = 0;
	root->position[Z] = RAND(-2.5, 2.5);	
	root->nb_level = (int)RAND(2,3);
	root->p_particule = create_Particule(root->position);
}

Particule* create_Particule(double pos[3])
{
	Particule* particule = (Particule*)calloc(1, sizeof(Particule));
			
	for (int i = 0; i < NB_COORDS; i++) {
		particule->position[i] = pos[i];
		particule->color[i] = (int)RAND(128, 255);
	}
	vector3D speed;
	do {
		SETVECTOR3D(speed, RAND(-1, 1), RAND(-1, 1), RAND(-1, 1));
	} while (!(speed.x) && !(speed.y) && !(speed.z));

	NORMALIZE(speed, speed);
	MUL(speed, speed, 6);
	particule->speed[X] = speed.x;
	particule->speed[Y] = speed.y;
	particule->speed[Z] = speed.z;
	particule->lifetime = RAND(3, 5);
	particule->size = RAND(0.02, 0.05);
	particule->children = 0;
	particule->p_father = NULL;
	particule->p_brother = NULL;	
	particule->p_children = NULL;
	
	return particule;
}

void update_Firework(Particule** particule, double dt, int nb_Niveaux, int nb_MAX) {	
	
	if (!(*particule)) return;
	
	update_Firework(&((*particule)->p_children), dt, nb_Niveaux + 1, nb_MAX);
	update_Firework(&((*particule)->p_brother), dt, nb_Niveaux, nb_MAX);
	if ((*particule)->lifetime > 0.0) {
		(*particule)->lifetime -= dt;
	}

	if (!((*particule)->children) && (*particule)->lifetime < 0 && nb_Niveaux < nb_MAX) {
		// Create children (8 - 24) (explosion).
		int nb_child = (int)RAND(8, 25);
		for (int i = 0; i < nb_child; i++) {
			(*particule)->p_children = create_child((*particule));
		}		
	}
	else if(!((*particule)->p_children) && (*particule)->lifetime < 0){
		// Destruction Totale
		free((*particule));
		(*particule) = NULL;		
	}
	else {
		vector3D g;
		SETVECTOR3D(g, 0, -9.81, 0);
		// Updating speed
		(*particule)->speed[X] = (*particule)->speed[0] + g.x * dt;
		(*particule)->speed[Y] = (*particule)->speed[1] + g.y * dt;
		(*particule)->speed[Z] = (*particule)->speed[2] + g.z * dt;

		// Updating and position.
		for (int i = 0; i < NB_COORDS; i++) {
			(*particule)->position[i] = ((*particule)->position[i]) + ((*particule)->speed[i]) * dt;
		}
	}	
}

Particule* create_child(Particule* parent) {

	Particule* child = (Particule*)calloc(1, sizeof(Particule));
	child->children = 0;
	for (int i = 0; i < NB_COLORS; i++) {
		child->color[i] = parent->color[i];
		child->position[i] = parent->position[i];
	}
	child->lifetime = 1;
	child->p_brother = parent->p_children;
	child->p_children = NULL;
	child->p_father = parent;	
	
	child->size = RAND(0.02, 0.05);

	vector3D speed;
	do {
		SETVECTOR3D(speed, RAND(-1, 1), RAND(-1, 1), RAND(-1, 1));
	} while (!(speed.x) && !(speed.y) && !(speed.z));

	NORMALIZE(speed, speed);
	MUL(speed, speed, 6);
	child->speed[X] = (2 + parent->speed[X]) * speed.x;
	child->speed[Y] = (2 + parent->speed[Y]) * speed.y;
	child->speed[Z] = (2 + parent->speed[Z]) * speed.z;
	return child;
}

