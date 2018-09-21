#include <stdio.h>
float taux(float VolumeA, float Taux, float VolumeD, float Start, float ConsoH, float VolAjou, float Heure, float TauxDil, float TauxAjou);

float taux(float VolumeA, float Taux, float VolumeD, float Start, float ConsoH, float VolAjou, float Heure, float TauxDil, float TauxAjou)
{
	float T;
	int i;
	T = (VolumeA * Taux + VolumeD * TauxDil)/(VolumeA + VolumeD);
	//printf("T0= %f\n", T);
	for (i = Start+1; i <= Heure; i++)
	{
		T = (((VolumeA + VolumeD - ConsoH) * T) + VolAjou * TauxAjou )/(((VolumeA + VolumeD) - ConsoH) + VolAjou); 
	}
	return T;
}

int main()
{
	float VolumeA, Taux, VolumeD, Start, ConsoH, VolAjou, Heure, minutes, TauxDil, TauxAjou;
	float res;
	
	printf("Volume d'alcool en L = ");
	scanf("%f", &VolumeA);
	
	printf("Taux d'alcool en pourcentage = ");
	scanf("%f", &Taux);
	
	printf("Volume de diluant1, en L = ");
	scanf("%f", &VolumeD);

	printf("Taux d'alcool du diluant1 en pourcentage = ");
	scanf("%f", &TauxDil);

	printf("Heure de début de la soirée (en système horaire sur 12h) : ");
	scanf("%f", &Start);
	
	printf("Volume consommé par heure = ");
	scanf("%f", &ConsoH);
	
	printf("Volume de diluant ajouté chaque heure = ");
	scanf("%f", &VolAjou);

	printf("Taux du diluant ajouté chaque heure = ");
	scanf("%f", &TauxAjou);
	
	printf("Calcul du taux d'alcool au bout de :\n");
	printf("Heures : ");
	scanf("%f", &Heure);
	printf("Minutes : ");
	scanf("%f", &minutes);

	Heure = Heure + Start;
	
	res = taux( VolumeA,  Taux, VolumeD, Start, ConsoH, VolAjou, Heure, TauxDil, TauxAjou);
	printf("Le taux d'alcool dans le punch est de %f\n", res);
	return 0;
}


