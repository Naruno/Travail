#include <stdio.h>
void Convertsectoh(int mats[],int ligneS,int math[], int ligneH){
	int a,j=0;
	for(int s=0;s<ligneH;s++){		
		for(int i=j;mats[i]-mats[j]<21600;i++){
			math[s]++;
			a=i;			
		}
		j=a;	
	}	
}

int SaisirCrottes(int mat[],int n){
	float somme=0;
	int crottes,indice=0;
	while(indice<n){
		printf("Crottes a l'heure %d : ",indice+1);
		scanf("%d",&crottes);
		if (crottes<0)
			break;
		mat[indice]=crottes;
		somme+=mat[indice];
		indice++;
	}	
	return somme;
}
void AfficheMatrice(int mat[7][4]){
	for(int u=0;u<7;u++){
		for(int y=0;y<4;y++){				
			printf("[ %d ]",mat[u][y]);									
		}	
		printf("\n");
	}	
}
void AfficheTableau(int tableau[],int lignes){
	for(int l=0;l<lignes;l++)
		printf("%d\n",tableau[l]);
}	
float stats(int tableau4[],int nbLignes){
	float n=0,r,v=0,t;
	for(int i=0;i<nbLignes;i++)		
		n+=tableau4[i];		
	for(int h=0;h<4;h++){
		switch(h){
			case 0:
				t=0.4;
				r=tableau4[0];
				break;
			case 1:
				t=0.2;
				r=tableau4[1];
				break;				
			case 2:
				t=0.1;
				r=tableau4[2];
				break;
			case 3:
				t=0.3;
				r=tableau4[3];
				break;
		}		
		v+=((r-n*t)*(r-n*t))/(n*t);	
		printf("[n=%.2f],[r=%.2f],[t=%.2f]\n",n,r,t);		
	}
	printf("v=%.2f\n",v);
	return v;
}
void MoyenneMAtrice(int mat1[],int nbLignes1, int mat2[][4], int nbLignes2){	
	float rang=0;	//,moyenne=0;
	for(int a=0;a<nbLignes2;a++){
		for(int j=0;j<4;j++){
				//mat2[a][j]=SaisirCrottes(mat1,nbLignes1);	
				mat2[a][j]=mat1[rang]; // reutiliser systeme de somme pour les 6h
				rang++;
				//moyenne+=mat2[a][j];				
		}	
		printf("\n");		
	}	
	AfficheMatrice(mat2);
	printf("\n");
}
int nbCrottesJour(int mat[][4],int nbLignes){
	int n=0;
	for(int o=0;o<7;o++){
		for(int p=0;p<4;p++)				
			n+=mat[o][p];									
		if(n<300)
			return o+1;
		n=0;	
	}
	return -1;
}	
int main(){		
	int total[7][4]={{0},{0},{0},{0},{0},{0},{0}}; // contient 3*4 elements // 3 represente les jours, 4, les colonnes de 6heures
	int inter[6]={0}; // les heures
	int statistique[4]={0};
	int transit[?]={0}; //quel taille doit faire un tableau de transit simplifie ??
	Simulate(transit,7,seed?); //seed = ?
	MoyenneMAtrice(inter,6,total,7);
	for(int f=0;f<7;f++){
		for(int m=0;m<4;m++)
			statistique[m]=total[f][m];									
		stats(statistique,4);
		printf("\n");
	}
	printf("%d\n",nbCrottesJour(total,7));
	return 0;
}