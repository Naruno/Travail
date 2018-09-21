#include "polynome.h"

int main(int argc,char **argv){
	
	if(argc>2){
		Polynome Res;
		Polynome poly;
		Polynome poly2;
		int load=ChargerPolynome(argv[1],&poly);
		int load2=ChargerPolynome(argv[2],&poly2);
	
		if (load!=0 && load2!=0)		
				return 0;		
		
		AfficherPolynome(&poly);
		printf("\n");
		AfficherPolynome(&poly2);
		printf("\n");
		
		if(poly.deg<poly2.deg)
			poly.coeffs=realloc(poly.coeffs,poly.deg*sizeof(float)+(poly2.deg-poly.deg)*sizeof(float));
			
		if(poly.deg>poly2.deg)
			poly2.coeffs=realloc(poly2.coeffs,poly2.deg*sizeof(float)+(poly.deg-poly2.deg)*sizeof(float));			
		
		MultPolynome(poly,poly2,&Res);
		AfficherPolynome(&Res);
		printf("\n");		
				
		LibererPolynome(&poly);		
		LibererPolynome(&poly2);			
	}
	else
		return 0;
	
	return 0;	
}