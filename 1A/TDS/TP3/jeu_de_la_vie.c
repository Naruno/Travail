#include "Configuration.h"
char **grid;

int get(void)
{
  struct termios oldt,newt;
  int ch,oldf;  
  tcgetattr(STDIN_FILENO,&oldt);
  newt=oldt;
  newt.c_lflag &=~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO,TCSANOW,&newt);
  oldf=fcntl(STDIN_FILENO,F_GETFL,0);
  fcntl(STDIN_FILENO,F_SETFL,oldf | O_NONBLOCK);
  ch=getchar();
  tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
  fcntl(STDIN_FILENO,F_SETFL,oldf);
  if(ch!=EOF)
  {
    ungetc(ch,stdin);
    return 1;
  }
  return 0;
}	

Config InitStruct(char* path){	
	Config info;
	FILE *fichier = fopen(path,"r");
	if(fichier != NULL){		
		fscanf(fichier,"largeur %d\nhauteur %d\nmotif %d\nnaissance %d %d %d %d %d %d %d %d\nsurvie %d %d %d %d %d %d %d %d\nimage %c\nvitesse %f\ncontinue %d",
		&info.largeur,&info.hauteur,&info.motif,&info.naissance[0],&info.naissance[1],&info.naissance[2],&info.naissance[3],&info.naissance[4],
		&info.naissance[5],&info.naissance[6],&info.naissance[7],&info.survie[0],&info.survie[1],&info.survie[2],&info.survie[3],&info.survie[4],
		&info.survie[5],&info.survie[6],&info.survie[7],&info.image,&info.vitesse,&info.nstop);		
		fclose(fichier);					   				   
	}return info;
}

int AlloGame(Config info){
	grid = (char**) calloc(info.hauteur,sizeof(char*));
	
	for (int i=0;i<info.hauteur;i++)
		grid[i]= (char*)calloc(info.largeur,sizeof(char));
		
	for (int j=0;j<info.hauteur;j++){
		for (int k=0;k<info.largeur;k++)
			grid[j][k]= ' ';
	}
	for (int n=0;n<8;n++){	
		if (info.motif<0 || info.motif>6 || info.largeur<5 || info.hauteur<5 || info.naissance[n]<0 || info.naissance[n]>8 || 
			info.survie[n]<0 || info.survie[n]>8 || info.nstop<0 || info.nstop>1){
			printf("Impossible de construire la grille ou le motif avec les valeures entrees\n");
			exit(0);
		}
	}
	switch(info.motif){
		
		case 1 :
			grid[(info.hauteur/2)][(info.largeur/2)-1] = info.image;
			grid[(info.hauteur/2)][(info.largeur/2)]= info.image;
			grid[(info.hauteur/2)][(info.largeur/2)+1]= info.image;
			break;
			
		case 2 :
			grid[(info.hauteur/2)-1][(info.largeur/2)-1]= info.image;
			grid[(info.hauteur/2)+1][(info.largeur/2)]= info.image;
			grid[(info.hauteur/2)-1][(info.largeur/2)+1]= info.image;
			grid[(info.hauteur/2)][(info.largeur/2)-1]= info.image;
			grid[(info.hauteur/2)][(info.largeur/2)+1]= info.image;
			grid[(info.hauteur/2)+1][(info.largeur/2)-1]= info.image;
			grid[(info.hauteur/2)+1][(info.largeur/2)+1]= info.image;
			break;
			
		case 3 :
			grid[(info.hauteur/2)-1][(info.largeur/2)-1]= info.image;
			grid[(info.hauteur/2)-1][(info.largeur/2)]= info.image;
			grid[(info.hauteur/2)-1][(info.largeur/2)+1]= info.image;
			grid[(info.hauteur/2)][(info.largeur/2)+1]= info.image;
			grid[(info.hauteur/2)+1][(info.largeur/2)]= info.image;
			break;
			
		case 4 :
			for (int i=0;i<info.hauteur;i++){
				for (int j=0;j<info.largeur;j++){
					if ((int)(rand()%2)==0)
						grid[i][j]= info.image;
					else 
						grid[i][j]= ' ';	
				}
			}break;
		
		case 5 :
			for (int i=0;i<info.hauteur;i++){
				for (int j=0;j<info.largeur/2;j++){				
					if ((int)(rand()%2)==0){					
						grid[i][j]= info.image;
						grid[i][info.largeur-j]= info.image;
					}
					else{						
						grid[i][j]=' ';
						grid[i][info.largeur-j]= ' ';					
					}
				}
			}break;	
	
		case 6 :
			for (int i=0;i<info.hauteur/2;i++){				
				for (int j=0;j<info.largeur;j++){					
					if ((int)(rand()%2)==0){						
						grid[i][j]= info.image;
						grid[info.hauteur-1-i][j]= info.image;
					}
					else{ 
						grid[i][j]= ' ';
						grid[info.hauteur-1-i][j]= ' ';					
					}
				}
			}break;		
	}
	return 0;		
}

int DrawGame(Config info, int gene){		
	printf("Appuyez pour Stopper\nGeneration %d\n",gene);
	gene++;
	
	for (int i=0;i<info.hauteur+2;i++){		
		for (int j=0;j<info.largeur+2;j++){			
			if (i==0 || i==info.hauteur+1)
				printf("~");			
			if ((j==0 || j==info.largeur+1) && (i!=0 && i<info.hauteur+1))
				printf("|");
			if (i>0 && j>0 && i<info.hauteur+1 && j<info.largeur+1){				
				if (i<=info.hauteur && j<=info.largeur)					
					printf("%c",grid[i-1][j-1]);							
			}
		}printf("\n");			
	}
	return gene;			
}

int IsInRange(int ligne,int colonne,Config info){	
	if (ligne>=0 && ligne<info.hauteur && colonne>=0 && colonne<info.largeur)
		return 1;
	else
		return 0;
}

int NbCasesAdj(int ligne,int colonne,Config info){
	int compteur=0;
	
	for (int i=-1;i<2;i++){		
		if ((ligne==info.hauteur-1) && i==1){			
			i++;
			continue;
		}					
		for (int j=-1;j<2;j++){			
				if (ligne==0 && i==-1)
					i++;					
				if ((colonne==0) && (j==-1)){					
					j++;					
				}				
				if ((colonne==info.largeur-1) && j==1){					
					j++;
					continue;					
				}
				if (grid[ligne+i][colonne+j]==info.image){
					compteur++;	
					if (i==0 && j==0)
						compteur--;
				}				
		}			
	}
	return compteur;
}

void UpdateGame(Config info){	
	char **Tab= (char**) calloc(info.hauteur,sizeof(char*));
	
	for (int i=0;i<info.hauteur;i++)
		Tab[i]= (char*) calloc(info.largeur,sizeof(char));
	
	for (int j=0;j<info.hauteur;j++){
		for (int k=0;k<info.largeur;k++)
			Tab[j][k]= ' ';	
	}		
	for (int i=0;i<info.hauteur;i++){
		for (int j=0;j<info.largeur;j++){
			if (IsInRange(i,j,info)==1){
				if ((grid[i][j]==info.image) && (NbCasesAdj(i,j,info)==(info.survie[0]) || NbCasesAdj(i,j,info)==(info.survie[1]) || 
												 NbCasesAdj(i,j,info)==(info.survie[2]) || NbCasesAdj(i,j,info)==(info.survie[3]) || 
												 NbCasesAdj(i,j,info)==(info.survie[4]) || NbCasesAdj(i,j,info)==(info.survie[5]) || 
												 NbCasesAdj(i,j,info)==(info.survie[6]) || NbCasesAdj(i,j,info)==(info.survie[7])))
					Tab[i][j]= info.image;
				if (grid[i][j]==' ' && (NbCasesAdj(i,j,info)==(info.naissance[0]) || NbCasesAdj(i,j,info)==(info.naissance[1]) || 
										NbCasesAdj(i,j,info)==(info.naissance[2]) || NbCasesAdj(i,j,info)==(info.naissance[3]) || 
										NbCasesAdj(i,j,info)==(info.naissance[4]) || NbCasesAdj(i,j,info)==(info.naissance[5]) || 
										NbCasesAdj(i,j,info)==(info.naissance[6]) || NbCasesAdj(i,j,info)==(info.naissance[0])))
					Tab[i][j]= info.image;				
			}
		}
	}
	for (int i=0;i<info.hauteur;i++){
		for (int j=0;j<info.largeur;j++){
			grid[i][j]= Tab[i][j];		    		
		}					
	}			
}

void PlayGame(Config info){
    int generation=0;	
	
	AlloGame(info);
	if (info.nstop==1){
		while (get()!=1){
			system("clear");
			generation=DrawGame(info,generation);							
			UpdateGame(info);
			usleep(info.vitesse*1000000);
			printf("\n");
		}	
	}
	else{
		char suite;
		do{
			system("clear");
			generation=DrawGame(info,generation);
			suite=getchar();
			UpdateGame(info);			
		}while(suite=='\n');
	}					
}

int main(){			
	Config info = InitStruct("Config.txt");	
	PlayGame(info);		
	free(grid);	
	return 0;
}