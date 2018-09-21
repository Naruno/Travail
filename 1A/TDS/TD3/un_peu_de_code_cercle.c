#include <stdio.h>
#define PI 3.141592
int main()
{
	float d,l,r;
    printf("Entrez une longueur et un diametre :\n");
    scanf("%g",&l);
    scanf("%g",&d);
    r=d/2;
    printf("Aire du cercle de rayon %g = %gcm²\nAire du rectangle de longueur %g et de largeur %g = %gcm²\n",r,PI*r*r,l,2*PI*r,2*PI*r*l);
    printf("Le cylindre ayant pour base le cercle de rayon %g et de hauteur %g a pour surface totale %gcm³\n",r,l,2*PI*r*(l+r));
	printf("Volume : %f\n",PI*r*r*l);
}
