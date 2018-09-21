#include <stdio.h>
int main()
{
    int a=10,*p_a=&a;
	printf("%d\n%d\n",a,*p_a); //Affiche la valeur de a de deux maniere differentes
    /* *p_a=NULL;
    *p_a=10; */ //Erreur de segmentation : Impossible de changer NULL
    float f;
    double *p2; // Impossible de faire pointer p2 sur f car ils sont de type different
	return 0;
}
