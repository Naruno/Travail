/* Biblioth�que cr��e pour repr�senter des graphes de fa�on graphique dans une fen�tre SDL */

#ifndef _GRAPHESDL_
#define _GRAPHESDL_

// R�solution �cran
#define RESX	600
#define RESY	600
// taille d'un sommet/�tat
#define SIZE	40
// Rayon pour la disposition initiale sur un cercle
#define RAYON	200
// Pour r�gler le positionnement des datagrammes par rapport au nom de la variable
#define OFFSETSEQ	10
#define OFFSETSEQ2	35

// nombre d'entr�es dans la s�quence enregistr�e
#define NB_SEQ	2048 

// temps (en ms) entre 2 fronts d'horloge montant & descendant (1/2 p�riode de l'horloge)
#define TIMER_DELAY	1000


#include "tools.h"
/* Inclusion de la biblioth�que sur les graphes */
#include "graphe.h"
#include "SDL.h"
#include "SDL_gfxPrimitives.h"

/* Structure de sommet pour l'affichage SDL
x,y : la position 2D du centre du sommet dans la fen�tre
size : la taille du carr� � dessin� pour le sommet
select : indique si le sommet a �t� s�lectionn� ou non
*/
typedef struct {
	int x, y;
	unsigned char size;
	SDL_Color c;
}SommetSDL;
typedef SommetSDL * pSommetSDL;

/* Structure de graphe pour l'affichage SDL
pG : pointeur sur le graphe � afficher (cf graphe.h pour la d�finition du type pGraphe)
tabSommetsSDL : informations supl�mentaires � stocker pour les sommets du graphe
*/
typedef struct {
	pGraphe pG;
	pSommetSDL tabSommetsSDL;
} GrapheSDL;
typedef GrapheSDL * pGrapheSDL;

// red�finition de type pour manipuler plus facilement la zone de dessin (fen�tre)
typedef SDL_Surface * pDessin;

/* Fonctions */
/*----------------------creerZoneDessin()--------------------------
Cr�e une fen�tre
A n'appeler qu'une seule fois au d�but de l'application
retourne un pointeur sur la surface SDL o� il faudra dessiner par la suite

ARGS:	titre : titre de la fen�tre Windows

VARS:	pDessin fenetre:	resultat (pointeur sur une surface SDL)

-----------------------------------------------------------*/
pDessin creerZoneDessin(char * titre);

/*----------------------creerGrapheSDL()--------------------------
Cr�e les compl�ments du graphe pass� en param�tre pour pouvoir le dessiner
retourne un pointeur le graphe modifi� pour pouvoir le dessiner avec SDL ou NULL si le graphe pass� en param�tre est vide

ARGS:	pG : pointeur sur le graphe

VARS:	pGrapheSDL pGSDL : pointeur r�sultat
int i : Variable de boucle
-----------------------------------------------------------*/
pGrapheSDL creerGrapheSDL(pGraphe pG);

/*----------------------dessinerSommet()--------------------------
Dessine un sommet dans la zone de dessin
retourne 1 si tout se passe bien, 0 sinon

ARGS:	pD : pointeur sur la zone de dessin
pGSDL : pointeur sur le graphe SDL
numSommet : num�ro du sommet � dessiner

VARS:	SDL_Rect r : rectangle de dessin � remplir avec la couleur du sommet

-----------------------------------------------------------*/
int dessinerSommet(pDessin pD, pGrapheSDL pGSDL, int numSommet);

/*----------------------dessinerArc()--------------------------
Dessine un arc dans la zone de dessin
retourne 1 si tout se passe bien, 0 sinon

ARGS:	pD : pointeur sur la zone de dessin
pGSDL : pointeur sur le graphe SDL
numSommetDepart : num�ro du sommet initial
numSommetArrivee : num�ro du sommet destination
att : attribut de l'arc
selec : pour d�finir la couleur de l'arc en fonction de la s�lection
VARS:

-----------------------------------------------------------*/
int dessinerArc(pDessin pD, pGrapheSDL pGSDL, int numSommetDepart, int numSommetArrivee, ATTRIBUT att, int selec);

/*----------------------dessinerGraphe()--------------------------
Dessine un graphe complet (sommets + arcs)
retourne 1 si tout se passe bien, 0 sinon

ARGS:	pD : pointeur sur la zone de dessin
pGSDL : pointeur sur le graphe SDL
E : valeur de l'entr�e
H : valeur de l'horolge
currentState : �tat courant
reset : �tat de l'entr�e Reset
states : historique pour affichage des datagrammes
seq : nombre d'�l�ments de l'historique
autoPlayH : est-on en horloge automatique ou pas

VARS:	int i,j : Variables de boucle

-----------------------------------------------------------*/
int dessinerGraphe(pDessin pD, pGrapheSDL pGSDL, int E, int H, int currentState, int reset, int states[NB_SEQ][3], int seq, int autoPlayH);

/*----------------------refreshZoneDessin()--------------------------
Permet redessiner toute la fen�tre et ainsi �tre s�r d'avoir redessin� toutes les modifications faites sur le graphe
retourne 1 si tout se passe bien, 0 sinon

ARGS:	pD : pointeur sur la zone de dessin

VARS:

-----------------------------------------------------------*/
int refreshZoneDessin(pDessin pD);

/*----------------------selectionnerSommet()--------------------------
Permet de marquer un sommet comme s�lectionn� ou non s�lectionn�
retourne 1 si tout se passe bien, 0 sinon

ARGS:	pGSDL : pointeur sur le graphe SDL
numSommet :  num�ro du sommet � marquer
select : valeur � attribuer (TRUE = s�lectionn�, FALSE = d�s�lectionn�)

VARS:

-----------------------------------------------------------*/
int selectionnerSommet(pGrapheSDL pGSDL, int numSommet, BOOL select);

/*------------------------getSommetWithPos()------------------------
R�cup�ration du num�ro du sommet sous la souris
Retourne -1 si aucun sommet trouv�, le num�ro du sommet sinon

ARGS:	pGrapheSDL pGSDL:	Pointeur sur grapheSDL a liberer
x,y : position sous laquelle on recherche le sommet

VARS:	int i : Variable de boucle
--------------------------------------------------------------*/
int getSommetWithPos(pGrapheSDL pGSDL, int x, int y);

/*------------------------freeGrapheSDL()------------------------
Liberation d'une structure GrapheSDL
Retourne 1 en cas de succes, 0 sinon

ARGS:	pGrapheSDL pGSDL:	Pointeur sur grapheSDL a liberer

VARS:
--------------------------------------------------------------*/
int freeGrapheSDL(pGrapheSDL pGSDL);


/*------------------------freeZoneDessin()------------------------
Liberation de la fen�tre SDL
Retourne 1 en cas de succes, 0 sinon

ARGS:	pDessin pD:	Pointeur sur la fen�tre � lib�rer

VARS:
--------------------------------------------------------------*/
int freeZoneDessin(pDessin pD);

/*------------------------variableAndState()------------------------
Ecriture du nom de la variable et de sa valeur / niveau �lectrique


ARGS:	x,y : position de l'affichage
name : nom de la variable
drawValue : doit-on afficher la valeur de la variable sous forme de niveau �lectrique?
value : valeur (0/1) � afficher sou forme num�rique et en niveau �lectrique
leftOrRightAlign : aligne la donn�e � gauche si =0, � droite sinon (0 par d�faut)

--------------------------------------------------------------*/
int variableAndState(pDessin pFenetre, int x, int y, char * name, int value, int drawValue, int leftOrRightAlign);

/*------------------------variableAndState()------------------------
Ecriture du nom de la variable et de sa valeur / niveau �lectrique


ARGS:	x,y : position de l'affichage
w,h : r�solution de la zone d'affichage
states : hostorique � afficher
seq : dernier �l�ment de l'historique � afficher

--------------------------------------------------------------*/
int drawStatesSeq(pDessin pFenetre, int x, int y, int w, int h, int states[NB_SEQ][3], int seq);

/*------------------------clockTimer()------------------------
fonction de callback pour le timer

ARGS:	interval : interval entre les 2 appel de fonction
param : param�tre utilisateur (non utilis�)

--------------------------------------------------------------*/
Uint32 clockTimer(Uint32 interval, void *param);

/*------------------------updateClock()------------------------
Mise � jour avec la modification des sorties en fonction des entr�es

ARGS:	pGSDL : pointeur sur le graphe
E : valeur d'entr�e
H : valeur d'horloge
pCurrentState : pointeur sur l'�taty courant
reset : valeur de nl'entr�e reset
states : historique
pSeq : nombre d'�l�ments dans l'historique (pass� par adresse)

--------------------------------------------------------------*/
BOOL updateClock(GrapheSDL * pGSDL, int E, int H, int *pCurrentState, int reset, int states[NB_SEQ][3], int *pSeq);

/*------------------------renderLoop()------------------------
Boucle de rendu avec gestion des �v�nements

ARGS:	pGraphe pG:	Pointeur sur le graphe � trasnformer en graphe "graphique" et sur lequel on pourra interagir

VARS:	BOOL finished : permet de boucler jusqu'� un appui sur le bouton droit de la souris
pDessin pD : pointeur sur la zone de dessin
pGrapheSDL pGSDL : pointeur sur le graphe "graphique"
--------------------------------------------------------------*/
int renderLoop(pGraphe pG);

#endif