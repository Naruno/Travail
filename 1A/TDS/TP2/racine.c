#include <stdio.h>
float square(int c,int a, float n,int f)
{
    float U=(float)c;
	int compteur=0;
    while (compteur<f){  
		if(U-((0.5)*(U+(a/U)))<n)
			break;
		printf("U%d =%f\n",compteur,U);
		U=(0.5)*(U+(a/U));
		compteur++;
	}
	printf("Un+1-Un<%.4f, a partir de U%d\n",n,compteur);		
    return U;
}
int main()
{
    int a,c,f;
    float n;
    printf("Quelle racine voulez vous approximer?\n");
    scanf("%d",&a);
	printf("Jusqu a quel rang?\n");
    scanf("%d",&f);	
	printf("Un+1-Un< a ?\n");
    scanf("%f",&n);
	printf("Uo=?\n");
    scanf("%d",&c);
    printf("%f\n",square(c,a,n,f));
}
