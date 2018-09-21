#include <stdio.h>
#include <time.h>
#include <math.h>
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

void DaysToMonths(float jours,Date_s *date){
	
	date->jour=(int)jours;
	date->mois=1;
	int bi=0;
	if (date->annee%4==0)
		bi=1;
	for (int j=1;jours>31;j++){
		
		switch(date->mois){
			
			case(1): 
				jours-=jJAN;
				date->mois++;
				break;
			case(2):
				jours-=jFEV+bi;
				date->mois++;
				break;
			case(3): 
				jours-=jMAR;
				date->mois++;
				break;
			case(4):
				jours-=jAVR;
				date->mois++;
				break;
			case(5): 
				jours-=jMAI;
				date->mois++;
				break;
			case(6):
				jours-=jJUIN;	
				date->mois++;
				break;
			case(7): 
				jours-=jJUI;
				date->mois++;
				break;
			case(8):
				jours-=jAOU;
				date->mois++;
				break;
			case(9): 
				jours-=jSEP;
				date->mois++;
				break;
			case(10):
				jours-=jOCT;
				date->mois++;
				break;
			case(11): 
				jours-=jNOV;
				date->mois++;
				break;
			case(12):
				jours-=jDEC;	
				date->mois++;
				break;												
		}
	}
	date->jour=(int)jours+1;	
}

int main(){
	
	Date_s date;
	float temps=time(NULL);
	
	temps=1970+temps/(60*60*24*365.25);
	date.annee=(int)temps;	
	DaysToMonths(((temps-(int)temps)*365.25),&date);
	printf("%d %d %d\n",date.jour,date.mois,date.annee);
	
	return 0;
}