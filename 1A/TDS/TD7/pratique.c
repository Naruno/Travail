#include <stdio.h>
#include <stdlib.h>

int* AllocTab(int n){	
	int *Tab = (int*) calloc(n, sizeof(int));
	return Tab;
}
void RandTab(int *Tab,int n,int min,int max){	
	for(int i=0;i<n;i++){		
		Tab[i]=(int)(rand()%(max + 1 - min)+min);		
		printf("%d\n",Tab[i]);	
	}	
}
void freeTab(void *Tab){
	free(Tab);
}

int** AllocMat(int nbRows, int nbCols){
	int**Mat=(int**)calloc(nbRows,sizeof(int*));
	for(int i=0;i<nbCols;i++)
		Mat[i]=(int*)calloc(nbCols,sizeof(int));		
	return Mat;
}

void RandMat (int **Mat,int nbRows, int nbCols, int min, int max){
	for(int i=0;i<nbRows;i++){
		for(int j=0;j<nbCols;j++){		
			Mat[i][j]=(int)(rand()%(max + 1 - min)+min);		
			printf("[%d]",Mat[i][j]);	
		}
		printf("\n");	
	}	
}
void freeMat(int **Mat){
	free(Mat);
}
int main(int argc, char **argv)
{
	int l,c,min,max;	
	printf("Nombre de lignes? ");
	scanf("%d",&l);
	printf("Nombre de colonnes? ");
	scanf("%d",&c);
	printf("Valeur minimum du tableau? ");
	scanf("%d",&min);
	printf("Valeur maximum du tableau? ");
	scanf("%d",&max);
	//int *Tab=AllocTab(l);
	int **Mat=AllocMat(l,c);
	/*
	RandTab(Tab,l,min,max);
	freeTab(Tab);*/	
	RandMat(Mat,l,c,min,max);
	freeMat(Mat);	
	return 0;
}
  
  
  