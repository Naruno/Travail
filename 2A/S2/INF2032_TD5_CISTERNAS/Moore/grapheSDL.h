/* Bibliothèque créée pour représenter des graphes de façon graphique dans une fenêtre SDL */

#ifndef _GRAPHESDL_
#define _GRAPHESDL_

// Résolution écran
#define RESX	600
#define RESY	600
// taille d'un sommet/état
#define SIZE	40
// Rayon pour la disposition initiale sur un cercle
#define RAYON	200
// Pour régler le positionnement des datagrammes par rapport au nom de la variable
#define OFFSETSEQ	10
#define OFFSETSEQ2	35

// nombre d'entrées dans la séquence enregistrée
#define NB_SEQ	2048 

// temps (en ms) entre 2 fronts d'horloge montant & descendant (1/2 période de l'horloge)
#define TIMER_DELAY	1000


#include "tools.h"
/* Inclusion de la bibliothèque sur les graphes */
#include "graphe.h"
#include "SDL.h"
#include "SDL_gfxPrimitives.h"

/* Structure de sommet pour l'affichage SDL
x,y : la position 2D du centre du sommet dans la fenêtre
size : la taille du carré à dessiné pour le sommet
select : indique si le sommet a été sélectionné ou non
*/
typedef struct {
	int x, y;
	unsigned char size;
	SDL_Color c;
}SommetSDL;
typedef SommetSDL * pSommetSDL;

/* Structure de graphe pour l'affichage SDL
pG : pointeur sur le graphe à afficher (cf graphe.h pour la définition du type pGraphe)
tabSommetsSDL : informations suplémentaires à stocker pour les sommets du graphe
*/
typedef struct {
	pGraphe pG;
	pSommetSDL tabSommetsSDL;
} GrapheSDL;
typedef GrapheSDL * pGrapheSDL;

// redéfinition de type pour manipuler plus facilement la zone de dessin (fenêtre)
typedef SDL_Surface * pDessin;

/* Fonctions */
/*----------------------creerZoneDessin()--------------------------
Crée une fenêtre
A n'appeler qu'une seule fois au début de l'application
retourne un pointeur sur la surface SDL où il faudra dessiner par la suite

ARGS:	titre : titre de la fenêtre Windows

VARS:	pDessin fenetre:	resultat (pointeur sur une surface SDL)

-----------------------------------------------------------*/
pDessin creerZoneDessin(char * titre);

/*----------------------creerGrapheSDL()--------------------------
Crée les compléments du graphe passé en paramètre pour pouvoir le dessiner
retourne un pointeur le graphe modifié pour pouvoir le dessiner avec SDL ou NULL si le graphe passé en paramètre est vide

ARGS:	pG : pointeur sur le graphe

VARS:	pGrapheSDL pGSDL : pointeur résultat
int i : Variable de boucle
-----------------------------------------------------------*/
pGrapheSDL creerGrapheSDL(pGraphe pG);

/*----------------------dessinerSommet()--------------------------
Dessine un sommet dans la zone de dessin
retourne 1 si tout se passe bien, 0 sinon

ARGS:	pD : pointeur sur la zone de dessin
pGSDL : pointeur sur le graphe SDL
numSommet : numéro du sommet à dessiner

VARS:	SDL_Rect r : rectangle de dessin à remplir avec la couleur du sommet

-----------------------------------------------------------*/
int dessinerSommet(pDessin pD, pGrapheSDL pGSDL, int numSommet);

/*----------------------dessinerArc()--------------------------
Dessine un arc dans la zone de dessin
retourne 1 si tout se passe bien, 0 sinon

ARGS:	pD : pointeur sur la zone de dessin
pGSDL : pointeur sur le graphe SDL
numSommetDepart : numéro du sommet initial
numSommetArrivee : numéro du sommet destination
att : attribut de l'arc
selec : pour définir la couleur de l'arc en fonction de la sélection
VARS:

-----------------------------------------------------------*/
int dessinerArc(pDessin pD, pGrapheSDL pGSDL, int numSommetDepart, int numSommetArrivee, ATTRIBUT att, int selec);

/*----------------------dessinerGraphe()--------------------------
Dessine un graphe complet (sommets + arcs)
retourne 1 si tout se passe bien, 0 sinon

ARGS:	pD : pointeur sur la zone de dessin
pGSDL : pointeur sur le graphe SDL
E : valeur de l'entrée
H : valeur de l'horolge
currentState : état courant
reset : état de l'entrée Reset
states : historique pour affichage des datagrammes
seq : nombre d'éléments de l'historique
autoPlayH : est-on en horloge automatique ou pas

VARS:	int i,j : Variables de boucle

-----------------------------------------------------------*/
int dessinerGraphe(pDessin pD, pGrapheSDL pGSDL, int E, int H, int currentState, int reset, int states[NB_SEQ][3], int seq, int autoPlayH);

/*----------------------refreshZoneDessin()--------------------------
Permet redessiner toute la fenêtre et ainsi être sûr d'avoir redessiné toutes les modifications faites sur le graphe
retourne 1 si tout se passe bien, 0 sinon

ARGS:	pD : pointeur sur la zone de dessin

VARS:

-----------------------------------------------------------*/
int refreshZoneDessin(pDessin pD);

/*----------------------selectionnerSommet()--------------------------
Permet de marquer un sommet comme sélectionné ou non sélectionné
retourne 1 si tout se passe bien, 0 sinon

ARGS:	pGSDL : pointeur sur le graphe SDL
numSommet :  numéro du sommet à marquer
select : valeur à attribuer (TRUE = sélectionné, FALSE = désélectionné)

VARS:

-----------------------------------------------------------*/
int selectionnerSommet(pGrapheSDL pGSDL, int numSommet, BOOL select);

/*------------------------getSommetWithPos()------------------------
Récupération du numéro du sommet sous la souris
Retourne -1 si aucun sommet trouvé, le numéro du sommet sinon

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
Liberation de la fenêtre SDL
Retourne 1 en cas de succes, 0 sinon

ARGS:	pDessin pD:	Pointeur sur la fenêtre à libérer

VARS:
--------------------------------------------------------------*/
int freeZoneDessin(pDessin pD);

/*------------------------variableAndState()------------------------
Ecriture du nom de la variable et de sa valeur / niveau électrique


ARGS:	x,y : position de l'affichage
name : nom de la variable
drawValue : doit-on afficher la valeur de la variable sous forme de niveau électrique?
value : valeur (0/1) à afficher sou forme numérique et en niveau électrique
leftOrRightAlign : aligne la donnée à gauche si =0, à droite sinon (0 par défaut)

--------------------------------------------------------------*/
int variableAndState(pDessin pFenetre, int x, int y, char * name, int value, int drawValue, int leftOrRightAlign);

/*------------------------variableAndState()------------------------
Ecriture du nom de la variable et de sa valeur / niveau électrique


ARGS:	x,y : position de l'affichage
w,h : résolution de la zone d'affichage
states : hostorique à afficher
seq : dernier élément de l'historique à afficher

--------------------------------------------------------------*/
int drawStatesSeq(pDessin pFenetre, int x, int y, int w, int h, int states[NB_SEQ][3], int seq);

/*------------------------clockTimer()------------------------
fonction de callback pour le timer

ARGS:	interval : interval entre les 2 appel de fonction
param : paramètre utilisateur (non utilisé)

--------------------------------------------------------------*/
Uint32 clockTimer(Uint32 interval, void *param);

/*------------------------updateClock()------------------------
Mise à jour avec la modification des sorties en fonction des entrées

ARGS:	pGSDL : pointeur sur le graphe
E : valeur d'entrée
H : valeur d'horloge
pCurrentState : pointeur sur l'étaty courant
reset : valeur de nl'entrée reset
states : historique
pSeq : nombre d'éléments dans l'historique (passé par adresse)

--------------------------------------------------------------*/
BOOL updateClock(GrapheSDL * pGSDL, int E, int H, int *pCurrentState, int reset, int states[NB_SEQ][3], int *pSeq);

/*------------------------renderLoop()------------------------
Boucle de rendu avec gestion des événements

ARGS:	pGraphe pG:	Pointeur sur le graphe à trasnformer en graphe "graphique" et sur lequel on pourra interagir

VARS:	BOOL finished : permet de boucler jusqu'à un appui sur le bouton droit de la souris
pDessin pD : pointeur sur la zone de dessin
pGrapheSDL pGSDL : pointeur sur le graphe "graphique"
--------------------------------------------------------------*/
int renderLoop(pGraphe pG);

#endif