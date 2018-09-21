#include <stdio.h>
typedef enum Mois{	
	JAN=1,FEV,MAR,AVR,MAI,JUIN,JUI,AOU,SEP,OCT,NOV,DEC
	
}Mois_s;

typedef enum JMois{	
	jJAN=31,jFEV=28,jMAR=31,jAVR=30,jMAI=31,jJUIN=30,jJUI=31,jAOU=30,jSEP=31,jOCT=31,jNOV=30,jDEC=31
	
}JMois_s;

typedef struct Date{	
	int annee;
	Mois_s mois;
	int jour;
	
}Date_s;

Date_s SaisirDate(Date_s date){
	
	printf("Entrez la date en chiffres :\nJour : ");
	scanf("%d",&date.jour);
	printf("Mois : ");
	scanf("%d",(int *)&date.mois);
	printf("Annee : ");
	scanf("%d",&date.annee);
	
	return date;
}

Date_s JoursAvantNoel(Date_s date){
	Date_s reste;
	reste.mois=12;
	reste.annee=0;
	reste.jour=25;
	reste.mois-=date.mois;
	reste.jour-=date.jour;		
	
	return reste;
}

Date_s Ajouter(Date_s date){
	int ajout=1;
	
	date.jour+=ajout;
	
	if (date.jour>30 && (date.mois==4 || date.mois==6 || date.mois==8 || date.mois==11)){
		
		date.jour=1;
		date.mois++;
		
	}
	if (date.mois==2 && date.jour>28){
		date.jour=1;
		date.mois++;
	}
		
	if (date.jour>31 && (date.mois==1 || date.mois==3 || date.mois==5 || date.mois==7 || date.mois==9 || date.mois==10 || date.mois==12)){
		
		date.jour=1;
		date.mois++;
		
	}
	if (date.mois>12){			
			date.annee++;
			date.mois=1;
	}
	
	return date;
}

int main(){
	Date_s date; //,reste;	
	//reste=JoursAvantNoel(SaisirDate(date));
	//printf("Il reste %d Mois et %d Jours avant noel !\n",reste.mois,reste.jour);
	
	date=Ajouter(SaisirDate(date));	
	printf("La date du jour est %d-%d-%d\n",date.jour,date.mois,date.annee);		
	
	return 0;	
}