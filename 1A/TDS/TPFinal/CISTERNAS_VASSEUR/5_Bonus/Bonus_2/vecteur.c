#include "vecteur.h"
#include "math.h"

Vecteur creerVect(float x,float y){ // Initialise la structure Vecteur
	
	Vecteur Init;
	Init.x=x;
	Init.y=y;
	return Init;	
}

Vecteur multScalVect(float s, Vecteur v){ // Multiplie les composantes x et y par s
	
	v.x*=s;
	v.y*=s;
	return v;
}

Vecteur addVect(Vecteur v1, Vecteur v2){ // Additionne les composantes en x et y et renvoie un nouveau vecteur
	
	Vecteur v;
	v.x=v1.x+v2.x;
	v.y=v1.y+v2.y;
	return v;	
}

float normVect(Vecteur v){ // Calcul la norme du Vecteur v
	
	float norme=sqrt(pow(v.x ,2)+pow(v.y,2));	
	return norme;	
}

Vecteur normaliseVect(Vecteur v){ // Egalise la norme du v a 1
	
	float norme=normVect(v);
	if (norme==0) 
		return creerVect(0,0); // Gere le cas de la division par 0
	Vecteur normalise=multScalVect(1/norme,v);
	return normalise;
}

Vecteur subVect(Vecteur v1, Vecteur v2){ // Retourne la soustraction de 2 vecteurs v1 et v2
	
	Vecteur v;
	v.x=v1.x-v2.x;
	v.y=v1.y-v2.y;
	return v;	
}