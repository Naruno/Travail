#include "polynome.h"

int ChargerPolynome (char *path, Polynome *p){
	
	int i;
	FILE *fichier = fopen(path,"r");
	if(fichier != NULL){
		
		fscanf(fichier,"%d\n",&p->deg);
	
		p->coeffs = (float*) calloc(p->deg+1,sizeof(float));
		
		for (i=p->deg;i>=0;i--){			
			fscanf(fichier,"%f ",&p->coeffs[i]);			
		}		
		fclose(fichier);
		return 0;
	}
	else{
		
		printf("Le fichier n'a pas pu être ouvert");
		return -1;
	}
}

void LibererPolynome(Polynome *p){
	
	free(p->coeffs);	
}

void AfficherPolynome(Polynome *p){
	
	int i;
	for (i=0;i<=p->deg;i++)
		printf("[%.1f]",p->coeffs[i]);
	
}

int EgalitePolynome(Polynome *p,Polynome *q){
	
	int i;
	if (p->deg == q->deg){
		
		for (i=0;i<p->deg;i++){
			
			if (p->coeffs[i]==q->coeffs[i]){}
			
			else 
				return 0;				
		}	
	}
	else{
		
		printf("Polynomes non comparables");
		return 0;
	
	}	
	return 1;	
}

int AddPolynome (Polynome P, Polynome Q, Polynome *Res){	
	
		int i;
		for(i=0;i<P.deg;i++)			
			Res->coeffs[i]=P.coeffs[i]+Q.coeffs[i];	
		
		return 0;	
		
}

int MultPolynome (Polynome P, Polynome Q, Polynome *Res){
	
	Res->deg=P.deg+Q.deg;
	Res->coeffs = (float*) calloc(Res->deg+1,sizeof(float));
	for (int k=0;k<=Res->deg;k++){
		Res->coeffs[k] = 0;
		
		for(int i=0;i<=k;i++)
			Res->coeffs[k] += P.coeffs[i]*Q.coeffs[k-i];
			
	}	
	return 0;
}