#include <stdio.h>

int main()
{	
	//int mat[2][4]={{10,20,30,40},{-10,-20,-30,-40}};
	int tab[4][6]= {{1},{1},{1},{1}}; // contient 3*7 elements
	tab[0][5]=-1; 
	for(int i=0;i<4;i++){
		for(int j=0;j<6;j++)
			printf("[ %d ]",tab[i][j]);			
		printf("\n");
	}		
	return 0;
}