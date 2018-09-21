#include <stdio.h>
#include <stdlib.h>

typedef struct Polynome_s{
	
	int deg;	   // Contient le degres du polynome
	float *coeffs; // Tableau contenant les coefficients du polynome	
}Polynome;

int ChargerPolynome (char *path, Polynome *p);
void LibererPolynome(Polynome *p);
void AfficherPolynome(Polynome *p);
int EgalitePolynome(Polynome *p,Polynome *q);
int AddPolynome (Polynome P, Polynome Q, Polynome *Res);
int MultPolynome (Polynome P, Polynome Q, Polynome *Res);