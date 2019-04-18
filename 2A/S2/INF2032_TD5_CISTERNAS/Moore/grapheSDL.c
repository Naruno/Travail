#include "grapheSDL.h"


/*----------------------creerZoneDessin()--------------------------
Cr�e une fen�tre
A n'appeler qu'une seule fois au d�but de l'application
retourne un pointeur sur la surface SDL o� il faudra dessiner par la suite

ARGS:	titre : titre de la fen�tre Windows

VARS:	pDessin fenetre:	resultat (pointeur sur une surface SDL)

-----------------------------------------------------------*/
pDessin creerZoneDessin(char * titre)
{
	pDessin fenetre;

	// Initialisation
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) return NULL;

	// Initialise le mode vid�o de la fen�tre
	fenetre = SDL_SetVideoMode(RESX, RESY, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	// Si on n'a pas r�ussi � cr�er la fen�tre on retourne une erreur
	if (fenetre == NULL) return NULL;

	// Ajout du titre sur la fen�tre
	SDL_WM_SetCaption(titre, NULL); // il est possible d'ajouter un ic�ne en haut � gauche de la fen�tre en passant le chemin du .ico dans le 2�me argument de la fonction

	return fenetre;
}

/*----------------------creerGrapheSDL()--------------------------
Cr�e les compl�ments du graphe pass� en param�tre pour pouvoir le dessiner
retourne un pointeur le graphe modifi� pour pouvoir le dessiner avec SDL ou NULL si le graphe pass� en param�tre est vide

ARGS:	pG : pointeur sur le graphe

VARS:	pGrapheSDL pGSDL : pointeur r�sultat
int i : Variable de boucle
-----------------------------------------------------------*/
pGrapheSDL creerGrapheSDL(pGraphe pG)
{
	pGrapheSDL pGSDL;
	int i;

	// Si pas de graphe pass� en param�tre on arr�te et on retourne NULL
	if (!pG) return NULL;

	// On alluoe la m�moire pour stocker le graphe SDL
	pGSDL = (pGrapheSDL)malloc(sizeof(GrapheSDL));
	// On retourne NULL si il y a eu probl�me � l'allocation
	if (!pGSDL) return NULL;

	// On fait le lien avec le graphe d�j� cr�� pr�c�demment en stockant un pointeur dessus
	pGSDL->pG = pG;

	// On cr�e le tableau de compl�ments d'information pour les sommets en utilisant le nombre de sommets stock� dans le graphe pass� en param�tre
	pGSDL->tabSommetsSDL = (pSommetSDL)malloc(sizeof(SommetSDL)*pG->nbSommets);
	// Si on a pas r�ussi � cr�e le tableau
	if (!pGSDL->tabSommetsSDL)
	{
		// On lib�re ce qui avait d�j� �t� allou� et on retourne NULL
		freeGrapheSDL(pGSDL);
		return NULL;
	}
	// On initialise les sommets un par un pour le dessin SDL
	for (i = 0; i < pG->nbSommets; i++)
	{
		// On dispose les sommets sur un cercle de rayon RAYON en les d�calant d'un angle constant calcul� � partir du nombre de sommets � afficher
		pGSDL->tabSommetsSDL[i].x = (int)(RESX / 2.0 + RAYON*cos(i * 2 * M_PI / (float)pGSDL->pG->nbSommets));
		pGSDL->tabSommetsSDL[i].y = (RESY - RESY / 10) / 2 + RESY / 10 + (int)(RAYON*sin(i * 2 * M_PI / (float)pGSDL->pG->nbSommets));
		// On initialise leur taille
		pGSDL->tabSommetsSDL[i].size = SIZE;
		// On les note comme non s�lectionn�s
		selectionnerSommet(pGSDL, i, FALSE);
		// On donne une couleur au sommet dans le r�f�rentiel HSV (numSommet*360/nbSommets,1,1)
		{

			// ----------------- conversion espace de couleur HSV vers RGB --------------------------
			// cf. wikipedia : http://en.wikipedia.org/wiki/HSL_and_HSV
			double  h, hi, himod2, x;
			pGSDL->tabSommetsSDL[i].c.r = pGSDL->tabSommetsSDL[i].c.g = pGSDL->tabSommetsSDL[i].c.b = 64;

			h = 360.0 / (float)pGSDL->pG->nbSommets*i;

			hi = h / 60.0;
			himod2 = hi;
			while (himod2 > 2) himod2 -= 2.0;
			x = 1 - fabs(himod2 - 1); // V = Shsv = 1

			switch ((int)hi) {
			case 0: pGSDL->tabSommetsSDL[i].c.r = 255; pGSDL->tabSommetsSDL[i].c.g = (Uint8)(x * 255); break;
			case 1: pGSDL->tabSommetsSDL[i].c.g = 255; pGSDL->tabSommetsSDL[i].c.r = (Uint8)(x * 255); break;
			case 2: pGSDL->tabSommetsSDL[i].c.g = 255; pGSDL->tabSommetsSDL[i].c.b = (Uint8)(x * 255); break;
			case 3: pGSDL->tabSommetsSDL[i].c.b = 255; pGSDL->tabSommetsSDL[i].c.g = (Uint8)(x * 255); break;
			case 4: pGSDL->tabSommetsSDL[i].c.b = 255; pGSDL->tabSommetsSDL[i].c.r = (Uint8)(x * 255); break;
			case 5: pGSDL->tabSommetsSDL[i].c.r = 255; pGSDL->tabSommetsSDL[i].c.b = (Uint8)(x * 255); break;
			}
			//-----------------------------------------------------------------------------------------
		}
	}
	return pGSDL;
}
/*----------------------dessinerSommet()--------------------------
Dessine un sommet dans la zone de dessin
retourne 1 si tout se passe bien, 0 sinon

ARGS:	pD : pointeur sur la zone de dessin
pGSDL : pointeur sur le graphe SDL
numSommet : num�ro du sommet � dessiner

VARS:	SDL_Rect r : rectangle de dessin � remplir avec la couleur du sommet

-----------------------------------------------------------*/
int dessinerSommet(pDessin pD, pGrapheSDL pGSDL, int numSommet)
{
	// d�claration du rectangle de dessin
	SDL_Rect r;

	// Teste si les param�tres sont valides, si ce n'est pas le cas on retourne 0
	if (!pD || !pGSDL || !pGSDL->tabSommetsSDL || numSommet<0 || numSommet >= pGSDL->pG->nbSommets) return 0;

	// Si le sommet est s�lectionn� on dessine un cadre blanc (un rectangle blanc en dessous du rectangle repr�sentant le sommet en le faisant d�passer)
	if (pGSDL->pG->tabSommets[numSommet].select)
	{
		// On dessine l'ombre
		filledCircleRGBA(pD, pGSDL->tabSommetsSDL[numSommet].x + 2, pGSDL->tabSommetsSDL[numSommet].y + 2, pGSDL->tabSommetsSDL[numSommet].size / 2 + 4, 0, 0, 0, 128);

		// On dessine un cercle blanc
		filledCircleRGBA(pD, pGSDL->tabSommetsSDL[numSommet].x, pGSDL->tabSommetsSDL[numSommet].y, pGSDL->tabSommetsSDL[numSommet].size / 2 + 4, 255, 255, 255, 255);
		// On dessine un cercle noir plus petit 
		filledCircleRGBA(pD, pGSDL->tabSommetsSDL[numSommet].x, pGSDL->tabSommetsSDL[numSommet].y, pGSDL->tabSommetsSDL[numSommet].size / 2 + 2, 0, 0, 0, 255);
	}

	// On configure le rectangle repr�sentant le sommet
	r.w = pGSDL->tabSommetsSDL[numSommet].size;
	r.h = pGSDL->tabSommetsSDL[numSommet].size;
	r.x = pGSDL->tabSommetsSDL[numSommet].x - pGSDL->tabSommetsSDL[numSommet].size / 2;
	r.y = pGSDL->tabSommetsSDL[numSommet].y - pGSDL->tabSommetsSDL[numSommet].size / 2;

	// On le dessine et on retourne le r�sultat du dessin (0 si il y a eut souci)
	{
		char value[256];

		// On dessine l'ombre
		filledCircleRGBA(pD, pGSDL->tabSommetsSDL[numSommet].x + 2, pGSDL->tabSommetsSDL[numSommet].y + 2, pGSDL->tabSommetsSDL[numSommet].size / 2, 0, 0, 0, 128);
		// On dessine le sommet
		filledCircleRGBA(pD, pGSDL->tabSommetsSDL[numSommet].x, pGSDL->tabSommetsSDL[numSommet].y, pGSDL->tabSommetsSDL[numSommet].size / 2, pGSDL->tabSommetsSDL[numSommet].c.r, pGSDL->tabSommetsSDL[numSommet].c.g, pGSDL->tabSommetsSDL[numSommet].c.b, 255);

		sprintf_s(value, 256, "Q%d", numSommet);
		stringRGBA(pD, 1 + pGSDL->tabSommetsSDL[numSommet].x - 7, 1 + pGSDL->tabSommetsSDL[numSommet].y - pGSDL->tabSommetsSDL[numSommet].size / 4, value, 0, 0, 0, 255);
		stringRGBA(pD, pGSDL->tabSommetsSDL[numSommet].x - 7, pGSDL->tabSommetsSDL[numSommet].y - pGSDL->tabSommetsSDL[numSommet].size / 4, value, 255, 255, 255, 255);

		sprintf_s(value, 256, "[%d]", pGSDL->pG->tabSommets[numSommet].out);
		stringRGBA(pD, 1 + pGSDL->tabSommetsSDL[numSommet].x - 10, 1 + pGSDL->tabSommetsSDL[numSommet].y, value, 0, 0, 0, 255);
		stringRGBA(pD, pGSDL->tabSommetsSDL[numSommet].x - 10, pGSDL->tabSommetsSDL[numSommet].y, value, 255, 255, 255, 255);

	}
	return 1;
}

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
int dessinerArc(pDessin pD, pGrapheSDL pGSDL, int numSommetDepart, int numSommetArrivee, ATTRIBUT att, int selec)
{
	//ATTRIBUT att;
	// Teste si les param�tres sont valides, si ce n'est pas le cas on retourne 0
	if (!pD || !pGSDL || !pGSDL->pG || !pGSDL->tabSommetsSDL || numSommetDepart<0 || numSommetDepart >= pGSDL->pG->nbSommets || numSommetArrivee<0 || numSommetArrivee >= pGSDL->pG->nbSommets) return 0;

	//att = pGSDL->pG->matrice[numSommetDepart][numSommetArrivee].value;
	// Si l'arc existe on le dessine avec une ligne et on affiche l'attribut � 1/3 de la distance en partant du sommet initial
	if (att >= 0)
	{
		// Chaine � afficher pour l'attribut
		char value[256];
		// couleur qui changera en fonction de la s�lection de l'arc
		Uint8 r, g, b;

		// choix de la couleur (blanc si non s�lectionn�, rouge sinon)
		r = g = b = 128;
		if (selec)	r = g = b = 255;

		// construction de la cha�ne � afficher
		sprintf_s(value, 256, "%s", att == ATTRIBUT_SPECIAL ? "X" : att ? "1" : "0");

		// Cas d'un rebouclage
		if (numSommetDepart == numSommetArrivee)
		{
			//Dessin d'un arc
			arcRGBA(pD, pGSDL->tabSommetsSDL[numSommetDepart].x - pGSDL->tabSommetsSDL[numSommetDepart].size / 2, pGSDL->tabSommetsSDL[numSommetDepart].y - pGSDL->tabSommetsSDL[numSommetDepart].size / 2, pGSDL->tabSommetsSDL[numSommetDepart].size / 2, 90, 360, r, g, b, 255);
			// Dessin de l'arriv�e du trait
			filledCircleRGBA(pD, pGSDL->tabSommetsSDL[numSommetArrivee].x - pGSDL->tabSommetsSDL[numSommetArrivee].size / 2 - 4, pGSDL->tabSommetsSDL[numSommetArrivee].y, 5, r, g, b, 255);
			// Dessin du texte avec ombrage
			stringRGBA(pD, 1 + pGSDL->tabSommetsSDL[numSommetDepart].x - pGSDL->tabSommetsSDL[numSommetArrivee].size, 1 + pGSDL->tabSommetsSDL[numSommetDepart].y - pGSDL->tabSommetsSDL[numSommetArrivee].size, value, 0, 0, 0, 255);
			stringRGBA(pD, pGSDL->tabSommetsSDL[numSommetDepart].x - pGSDL->tabSommetsSDL[numSommetArrivee].size, pGSDL->tabSommetsSDL[numSommetDepart].y - pGSDL->tabSommetsSDL[numSommetArrivee].size, value, r, g, b, 255);
		}
		// Cas d'un arc rectiligne
		else
		{
			float dx, dy, norm;
			dx = (float)(pGSDL->tabSommetsSDL[numSommetArrivee].x - pGSDL->tabSommetsSDL[numSommetDepart].x);
			dy = (float)(pGSDL->tabSommetsSDL[numSommetArrivee].y - pGSDL->tabSommetsSDL[numSommetDepart].y);

			norm = (float)sqrt(dx*dx + dy*dy);

			if (2 * norm > pGSDL->tabSommetsSDL[numSommetDepart].size + pGSDL->tabSommetsSDL[numSommetArrivee].size)
			{
				float dx2, dy2;
				dx /= norm;
				dy /= norm;

				// On effectue une petite rotation pour que les arcs de A>B et B>A ne soient pas confondus
				dx2 = (float)(dx*cos(0.4) + dy*sin(0.4));
				dy2 = (float)(-dx*sin(0.4) + dy*cos(0.4));

				//dessin du trait
				aalineRGBA(pD, pGSDL->tabSommetsSDL[numSommetDepart].x + (int)(dx*pGSDL->tabSommetsSDL[numSommetDepart].size / 2), pGSDL->tabSommetsSDL[numSommetDepart].y + (int)(dy*pGSDL->tabSommetsSDL[numSommetDepart].size / 2), pGSDL->tabSommetsSDL[numSommetArrivee].x - (int)(dx2*pGSDL->tabSommetsSDL[numSommetArrivee].size / 2), pGSDL->tabSommetsSDL[numSommetArrivee].y - (int)(dy2*pGSDL->tabSommetsSDL[numSommetArrivee].size / 2), r, g, b, 255);
				// Dessin de l'arriv�e du trait
				filledCircleRGBA(pD, pGSDL->tabSommetsSDL[numSommetArrivee].x - (int)(dx2*(pGSDL->tabSommetsSDL[numSommetArrivee].size / 2 + 4)), pGSDL->tabSommetsSDL[numSommetArrivee].y - (int)(dy2*(pGSDL->tabSommetsSDL[numSommetArrivee].size / 2 + 4)), 5, r, g, b, 255);
				// Dessin du texte avec ombrage
				stringRGBA(pD, 1 + pGSDL->tabSommetsSDL[numSommetDepart].x + (pGSDL->tabSommetsSDL[numSommetArrivee].x - pGSDL->tabSommetsSDL[numSommetDepart].x) / 3, 1 + pGSDL->tabSommetsSDL[numSommetDepart].y + (pGSDL->tabSommetsSDL[numSommetArrivee].y - pGSDL->tabSommetsSDL[numSommetDepart].y) / 3, value, 0, 0, 0, 255);
				stringRGBA(pD, pGSDL->tabSommetsSDL[numSommetDepart].x + (pGSDL->tabSommetsSDL[numSommetArrivee].x - pGSDL->tabSommetsSDL[numSommetDepart].x) / 3, pGSDL->tabSommetsSDL[numSommetDepart].y + (pGSDL->tabSommetsSDL[numSommetArrivee].y - pGSDL->tabSommetsSDL[numSommetDepart].y) / 3, value, r, g, b, 255);
			}
		}
	}

	// Retour
	return 1;
}


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
int dessinerGraphe(pDessin pD, pGrapheSDL pGSDL, int E, int H, int currentState, int reset, int states[NB_SEQ][3], int seq, int autoPlayH)
{
	int i;

	pGSDL->pG->tabSommets[currentState].select = TRUE;


	// Teste si les param�tres sont valides, si ce n'est pas le cas on retourne 0
	if (!pD || !pGSDL || !pGSDL->pG || !pGSDL->tabSommetsSDL)
		return 0;

	// remplit la zone de dessin en noir
	SDL_FillRect(pD, NULL, SDL_MapRGB(pD->format, 0, 0, 0));


	// On boucle sur toute la matrice du graphe
	for (i = 0; i < pGSDL->pG->nbSommets; i++)
	{
		// Un sommet a 2 sommets voisins au maximum
		int selectArc = (currentState == i ? 1 : 0);

		// m�me sommet voisin pour les 2 valeurs d'entr�e (E)
		if (pGSDL->pG->tabSommets[i].adj[0] == pGSDL->pG->tabSommets[i].adj[1])
		{
			// On dessine l'arc en pond�rant par "0/1"
			dessinerArc(pD, pGSDL, i, pGSDL->pG->tabSommets[i].adj[0], ATTRIBUT_SPECIAL, selectArc);
		}
		else
		{
			int j;

			// On dessine les 2 arcs
			for (j = 0; j < 2; j++)
			{
				dessinerArc(pD, pGSDL, i, pGSDL->pG->tabSommets[i].adj[j], j, E == j ? selectArc : 0);
			}
		}

	}

	// On boucle sur tous les sommets du graphe pour les dessiner
	for (i = 0; i < pGSDL->pG->nbSommets; i++)	dessinerSommet(pD, pGSDL, i);

	{
		char chaineAuto[16];

		SDL_Rect r;
		r.x = r.y = 0;
		r.w = RESX;
		r.h = RESY / 10;

		SDL_FillRect(pD, &r, SDL_MapRGB(pD->format, 64, 64, 64));

		r.x = 92;
		r.y = 25;
		r.w = 100;
		r.h = RESY / 10 - 30;

		lineRGBA(pD, r.x + r.w / 2 - 30, r.y - 5, r.x + r.w / 2 - 30, r.y, 255, 255, 255, 255);
		lineRGBA(pD, r.x - 10, r.y + 10, r.x + r.w + 10, r.y + 10, 255, 255, 255, 255);
		lineRGBA(pD, r.x - 10, r.y + r.h - 10, r.x + r.w + 10, r.y + r.h - 10, 255, 255, 255, 255);


		SDL_FillRect(pD, &r, SDL_MapRGB(pD->format, 255, 255, 255));
		r.x++;
		r.y++;
		r.w -= 2;
		r.h -= 2;
		SDL_FillRect(pD, &r, SDL_MapRGB(pD->format, 0, 0, 0));


		if (autoPlayH)
		{
			strcpy_s(chaineAuto, 16, ">>>");
		}
		else
		{
			strcpy_s(chaineAuto, 16, "||");
		}
		stringRGBA(pD, 6, 6, chaineAuto, 0, 0, 0, 255);
		stringRGBA(pD, 5, 5, chaineAuto, 255, 0, 0, 255);


		variableAndState(pD, r.x + r.w / 2 - 32, 5, "R", reset, TRUE, 0);
		variableAndState(pD, r.x + r.w / 2 - 70, 32, "E", E, TRUE, 1);
		variableAndState(pD, r.x + r.w / 2 - 70, 53, "H", H, TRUE, 1);
		variableAndState(pD, r.x + r.w / 2 + 70, 32, "Etat", currentState, FALSE, 0);
		variableAndState(pD, r.x + r.w / 2 + 70, 53, "out", pGSDL->pG->tabSommets[currentState].out, TRUE, 0);

		drawStatesSeq(pD, 350, 0, RESX - 350, RESY / 10, states, seq);
	}

	// Retour
	return 1;
}


/*----------------------refreshZoneDessin()--------------------------
Permet redessiner toute la fen�tre et ainsi �tre s�r d'avoir redessin� toutes les modifications faites sur le graphe
retourne 1 si tout se passe bien, 0 sinon

ARGS:	pD : pointeur sur la zone de dessin

VARS:

-----------------------------------------------------------*/
int refreshZoneDessin(pDessin pD)
{
	// Teste si la zone existe retourne 0 sinon
	if (!pD) return 0;

	// Redessine toute la surface de la zone de dessin
	SDL_UpdateRect(pD, 0, 0, 0, 0);

	// Retour
	return 1;
}

/*----------------------selectionnerSommet()--------------------------
Permet de marquer un sommet comme s�lectionn� ou non s�lectionn�
retourne 1 si tout se passe bien, 0 sinon

ARGS:	pGSDL : pointeur sur le graphe SDL
numSommet :  num�ro du sommet � marquer
select : valeur � attribuer (TRUE = s�lectionn�, FALSE = d�s�lectionn�)

VARS:

-----------------------------------------------------------*/
int selectionnerSommet(pGrapheSDL pGSDL, int numSommet, BOOL select)
{
	// Teste si les param�tres d'entr�e sont valides, retourne 0 si ce n'est pas le cas
	if (!pGSDL || !pGSDL->pG || !pGSDL->pG->tabSommets || numSommet<0 || numSommet >= pGSDL->pG->nbSommets) return 0;
	// On marque le sommet comme s�lectionn� ou non s�lectionn�
	pGSDL->pG->tabSommets[numSommet].select = select;
	return 1;
}
/*------------------------getSommetWithPos()------------------------
R�cup�ration du num�ro du sommet sous la souris
Retourne -1 si aucun sommet trouv�, le num�ro du sommet sinon

ARGS:	pGrapheSDL pGSDL:	Pointeur sur grapheSDL a liberer
x,y : position sous laquelle on recherche le sommet

VARS:	int i : Variable de boucle
--------------------------------------------------------------*/
int getSommetWithPos(pGrapheSDL pGSDL, int x, int y)
{
	int i;

	// Teste les param�tres d'entr�e et retourne -1 si il y a un souci
	if (!pGSDL || !pGSDL->tabSommetsSDL) return -1;

	for (i = 0; i < pGSDL->pG->nbSommets; i++)
	{
		if (x >= pGSDL->tabSommetsSDL[i].x - pGSDL->tabSommetsSDL[i].size / 2 && x<pGSDL->tabSommetsSDL[i].x + pGSDL->tabSommetsSDL[i].size / 2 &&
			y >= pGSDL->tabSommetsSDL[i].y - pGSDL->tabSommetsSDL[i].size / 2 && y<pGSDL->tabSommetsSDL[i].y + pGSDL->tabSommetsSDL[i].size / 2)
			return i;
	}
	return -1;
}
/*------------------------freeGraphe()------------------------
Liberation d'une structure GrapheSDL
Retourne 1 en cas de succes, 0 sinon

ARGS:	pGrapheSDL pGSDL:	Pointeur sur grapheSDL a liberer

VARS:
--------------------------------------------------------------*/
int freeGrapheSDL(pGrapheSDL pGSDL){

	// Analyse des arguments
	if (pGSDL == NULL)
		return 0;

	//Liberation du tableau de compl�ments pour les sommets
	if (pGSDL->tabSommetsSDL) free(pGSDL->tabSommetsSDL);

	// Liberation du graphe
	if (pGSDL->pG) freeGraphe(pGSDL->pG);

	// Liberation de la structure GrapheSDL
	free(pGSDL);

	// Retour
	return 1;
}
/*------------------------freeZoneDessin()------------------------
Liberation de la fen�tre SDL
Retourne 1 en cas de succes, 0 sinon

ARGS:	pDessin pD:	Pointeur sur la fen�tre � lib�rer

VARS:
--------------------------------------------------------------*/
int freeZoneDessin(pDessin pD)
{
	// Si la zone de dessin n'existe pas on retourne 0
	if (!pD) return 0;

	// Si elle existe on la lib�re
	SDL_FreeSurface(pD);

	// Retour
	return 1;
}
/*------------------------variableAndState()------------------------
Ecriture du nom de la variable et de sa valeur / niveau �lectrique


ARGS:	x,y : position de l'affichage
name : nom de la variable
drawValue : doit-on afficher la valeur de la variable sous forme de niveau �lectrique?
value : valeur (0/1) � afficher sou forme num�rique et en niveau �lectrique
leftOrRightAlign : aligne la donn�e � gauche si =0, � droite sinon (0 par d�faut)

--------------------------------------------------------------*/
int variableAndState(pDessin pFenetre, int x, int y, char * name, int value, int drawValue, int leftOrRightAlign)
{
	char chaine[256];
	int sizeName = strlen(name);
	int offset = leftOrRightAlign ? sizeName * 8 + 56 : 0;

	sprintf_s(chaine, 256, "%s = %d", name, value);
	stringRGBA(pFenetre, 1 + x - offset, 1 + y, chaine, 0, 0, 0, 255);
	stringRGBA(pFenetre, x - offset, y, chaine, 255, 255, 255, 255);
	if (drawValue)
	{

		lineRGBA(pFenetre, 1 + x + 40 + sizeName * 8 - offset, 1 + y + 6 - 8 * value, 1 + x + 56 + sizeName * 8 - offset, 1 + y + 6 - 8 * value, 0, 0, 0, 255);
		lineRGBA(pFenetre, x + 40 + sizeName * 8 - offset, y + 6 - 8 * value, x + 56 + sizeName * 8 - offset, y + 6 - 8 * value, 255, 255, 255, 255);
	}
	return 1;
}
/*------------------------variableAndState()------------------------
Ecriture du nom de la variable et de sa valeur / niveau �lectrique


ARGS:	x,y : position de l'affichage
w,h : r�solution de la zone d'affichage
states : hostorique � afficher
seq : dernier �l�ment de l'historique � afficher

--------------------------------------------------------------*/
int drawStatesSeq(pDessin pFenetre, int x, int y, int w, int h, int states[NB_SEQ][3], int seq)
{
	char chaineE[2048] = "";
	char chaineOut[2048] = "";
	char chaineState[2048] = "";
	int i, E = 0, out = 0;

	sprintf_s(chaineE, 2048, "E   ");
	sprintf_s(chaineOut, 2048, "Out ");
	sprintf_s(chaineState, 2048, "Etat");


	for (i = 0; i < min(seq, (w - OFFSETSEQ2) / 16); i++)
	{
		int index = i;
		if (seq>(w - OFFSETSEQ2) / 16) index += seq - (w - OFFSETSEQ2) / 16;


		sprintf_s(chaineE, 2048, "%s %d", chaineE, states[index][0]);
		sprintf_s(chaineOut, 2048, "%s %d", chaineOut, states[index][1]);
		sprintf_s(chaineState, 2048, "%s %d", chaineState, states[index][2]);

		// Dessin de la s�quence E
		E = states[index][0];
		if (i != 0 && E != states[index - 1][0])
		{
			// On dessine une ligne verticale
			lineRGBA(pFenetre, 1 + x + OFFSETSEQ2 + i * 16, 1 + y + h / 6 + 4, 1 + x + OFFSETSEQ2 + i * 16, 1 + y + h / 6 + 4 - 12, 0, 0, 0, 255);
			lineRGBA(pFenetre, x + OFFSETSEQ2 + i * 16, y + h / 6 + 4, x + OFFSETSEQ2 + i * 16, y + h / 6 + 4 - 12, 255, 255, 255, 255);
		}
		lineRGBA(pFenetre, 1 + x + OFFSETSEQ2 + i * 16, 1 + y + h / 6 + 4 - 12 * E, 1 + x + OFFSETSEQ2 + (i + 1) * 16, 1 + y + h / 6 + 4 - 12 * E, 0, 0, 0, 255);
		lineRGBA(pFenetre, x + OFFSETSEQ2 + i * 16, y + h / 6 + 4 - 12 * E, x + OFFSETSEQ2 + (i + 1) * 16, y + h / 6 + 4 - 12 * E, 255, 255, 255, 255);
		// Dessin de la s�quence Out
		out = states[index][1];
		if (i != 0 && out != states[index - 1][1])
		{
			// On dessine une ligne verticale
			lineRGBA(pFenetre, 1 + x + OFFSETSEQ2 + i * 16, 1 + y + h / 6 + 4 + h / 3, 1 + x + OFFSETSEQ2 + i * 16, 1 + y + h / 6 + 4 + h / 3 - 12, 0, 0, 0, 255);
			lineRGBA(pFenetre, x + OFFSETSEQ2 + i * 16, y + h / 6 + 4 + h / 3, x + OFFSETSEQ2 + i * 16, y + h / 6 + 4 + h / 3 - 12, 255, 255, 255, 255);
		}
		lineRGBA(pFenetre, 1 + x + OFFSETSEQ2 + i * 16, 1 + y + h / 6 + 4 + h / 3 - 12 * out, 1 + x + OFFSETSEQ2 + (i + 1) * 16, 1 + y + h / 6 + 4 + h / 3 - 12 * out, 0, 0, 0, 255);
		lineRGBA(pFenetre, x + OFFSETSEQ2 + i * 16, y + h / 6 + 4 + h / 3 - 12 * out, x + OFFSETSEQ2 + (i + 1) * 16, y + h / 6 + 4 + h / 3 - 12 * out, 255, 255, 255, 255);
	}


	stringRGBA(pFenetre, 1 + x, 1 + y + h / 6 - 5, chaineE, 0, 0, 0, 255);
	stringRGBA(pFenetre, x, y + h / 6 - 5, chaineE, 255, 255, 255, 255);
	stringRGBA(pFenetre, 1 + x, 1 + y + h / 3 + h / 6 - 5, chaineOut, 0, 0, 0, 255);
	stringRGBA(pFenetre, x, y + h / 3 + h / 6 - 5, chaineOut, 255, 255, 255, 255);
	stringRGBA(pFenetre, 1 + x, 1 + y + 2 * h / 3 + h / 6 - 5, chaineState, 0, 0, 0, 255);
	stringRGBA(pFenetre, x, y + 2 * h / 3 + h / 6 - 5, chaineState, 255, 255, 255, 255);


	return 1;
}


/*------------------------clockTimer()------------------------
fonction de callback pour le timer

ARGS:	interval : interval entre les 2 appel de fonction
param : param�tre utilisateur (non utilis�)

--------------------------------------------------------------*/
Uint32 clockTimer(Uint32 interval, void *param)
{
	SDL_Event event;
	SDL_UserEvent userevent;

	// On g�n�re un �v�nement utilisateur tous les "interval" ms
	userevent.type = SDL_USEREVENT;
	userevent.code = 0;
	userevent.data1 = NULL;
	userevent.data2 = NULL;

	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);
	return(interval);
}

/*------------------------updateClock()------------------------
Mise � jour avec la modification des sorties en fonction des entr�es

ARGS:	pGSDL : pointeur sur le graphe
E : valeur d'entr�e
H : valeur d'horloge
pCurrentState : pointeur sur l'�tat courant
reset : valeur de nl'entr�e reset
states : historique
pSeq : nombre d'�l�ments dans l'historique (pass� par adresse)

--------------------------------------------------------------*/
BOOL updateClock(GrapheSDL * pGSDL, int E, int H, int *pCurrentState, int reset, int states[NB_SEQ][3], int *pSeq){

	if (H){
		pGSDL->pG->tabSommets[*pCurrentState].select = 0;
		*pCurrentState = pGSDL->pG->tabSommets[*pCurrentState].adj[E];
	}	
	else return FALSE;
	if (reset) {		
		pGSDL->pG->tabSommets[*pCurrentState].select = 0;
		*pCurrentState = 0;
		*pSeq = 0;
	}
	/* on s'occupe aussi de l'historique */
	states[*pSeq][0] = E;
	states[*pSeq][1] = pGSDL->pG->tabSommets[*pCurrentState].out;
	states[*pSeq][2] = *pCurrentState;
	(*pSeq)++;
	return TRUE;
}

/*------------------------renderLoop()------------------------
Boucle de rendu avec gestion des �v�nements

ARGS:	pGraphe pG:	Pointeur sur le graphe � trasnformer en graphe "graphique" et sur lequel on pourra interagir

VARS:	BOOL finished : permet de boucler jusqu'� un appui sur le bouton droit de la souris
pDessin pD : pointeur sur la zone de dessin
pGrapheSDL pGSDL : pointeur sur le graphe "graphique"
--------------------------------------------------------------*/
int renderLoop(pGraphe pG)
{
	// Variable pour contr�ler la sortie de la boucle de rendu 
	BOOL finished = FALSE;
	// Pointeur sur la zone de dessin
	pDessin pD = NULL;
	// Pointeur sur le graphe SDL
	pGrapheSDL pGSDL = NULL;
	// Sommet s�lectionn� pour le d�placement souris
	int selec = -1;

	// Sommet s�lectionn� pour notifier l'�tat courant
	int currentState = 0;
	// Entr�e de commande (peut prendre 0 ou 1 en fonction de l'�tat de la touche CTRL)
	int E = 0;
	// Entr�e Horloge (peut prendre 0 ou 1 en fonction de l'�tat de la touche SPACE)
	int H = 0;
	// Pour g�n�rer une horloge automatiquement
	int autoPlayH = 0;
	// timer pour g�n�rer le signal d'horloge
	SDL_TimerID  tID = NULL; // Init perso.

	// entr�e Reset de la machine
	int reset = 0;

	// sauvegarde de la s�quence de E et out dans le temps
	int states[NB_SEQ][3];
	// num�ro de la s�quence courante
	int seq = 1;
	int seqDisplay = seq; // pour pouvoir faire un retour arri�re dans la s�quence enregistr�e (avec les touches GAUCHE/DROITE)
	int seqOffset = 0;
	// offset entre la souris et le centre du sommet en cours de manipulation	
	int offsetX, offsetY;

	int refresh = 0;
	int count = 0; // pour compter le nombre de rafraichissement quand on veut scrollerr les datagrammes
	// On cr�e la zone de dessin
	pD = creerZoneDessin("Machine de Moore");
	if (!pD) return 0;


	// On cr�e le graphe SDL � partir du graphe pass� en param�tre
	pGSDL = creerGrapheSDL(pG);
	if (!pGSDL) return 0;


	// �tat initial
	states[0][0] = 0;
	states[0][1] = pG->tabSommets[0].out;
	states[0][2] = 0;

	// On dessine le graphe dans la zone de dessin
	if (!dessinerGraphe(pD, pGSDL, E, H, currentState, reset, states, seq, autoPlayH) || !refreshZoneDessin(pD)) return 0;

	// On boucle 
	while (!finished)
	{

		// On r�cup�re les �v�nements sur la fen�tre
		SDL_Event evt;
		SDL_PumpEvents();


		// On traite les �v�nements un par un 
		while (SDL_PollEvent(&evt) && !finished)
		{
			switch (evt.type)
			{
			case SDL_USEREVENT:
				// CHANGEMENT DE VALEUR POUR H AVEC LE TIMER
				H = (H == 1) ? 0 : 1;
				updateClock(pGSDL, E, H, &currentState, reset, states, &seq);		

				seqDisplay = seq;
				refresh = 1;
				break;

				// Bouton souris appuy�
			case SDL_MOUSEBUTTONDOWN:
			{
				int x, y;

				// On r�cup�re l'�tat de la souris + les coordonn�es du pointeur
				int mouseState = SDL_GetMouseState(&x, &y);

				// Bouton gauche appuy�
				if (mouseState&SDL_BUTTON(1) && selec == -1)
				{
					// On r�cup�re le sommet sous la souris
					selec = getSommetWithPos(pGSDL, x, y);
					// Si le sommet est valide on r�cup�re l'offset entre la souris et le centre du sommet
					if (selec >= 0 && selec < pGSDL->pG->nbSommets)
					{
						offsetX = pGSDL->tabSommetsSDL[selec].x - x;
						offsetY = pGSDL->tabSommetsSDL[selec].y - y;
					}
				}
			}
				break;
				// Bouton souris appuy�
			case SDL_MOUSEBUTTONUP:
			{
				int x, y;

				// On r�cup�re l'�tat de la souris + les coordonn�es du pointeur
				int mouseState = SDL_GetMouseState(&x, &y);

				// Bouton gauche relach�
				if (!(mouseState&SDL_BUTTON(1)) && selec != -1)
				{
					// On d�s�lectionne le sommet et on arr�te le drag & drop
					selec = -1;
				}

			}
				break;
				// Bouton souris appuy�
			case SDL_MOUSEMOTION:
			{
				int x, y;
				// On r�cup�re l'�tat de la souris + les coordonn�es du pointeur
				int mouseState = SDL_GetMouseState(&x, &y);

				if (selec != -1)
				{
					pGSDL->tabSommetsSDL[selec].x = x + offsetX;
					pGSDL->tabSommetsSDL[selec].y = y + offsetY;

					pGSDL->tabSommetsSDL[selec].x = max(SIZE, min(RESX - SIZE, pGSDL->tabSommetsSDL[selec].x));
					pGSDL->tabSommetsSDL[selec].y = max(RESY / 10 + SIZE, min(RESY - SIZE, pGSDL->tabSommetsSDL[selec].y));

					refresh = 1;
				}
			}
				break;
				// Touche clavier appuy�e
			case SDL_KEYDOWN:
				// Si c'est ECHAP on quitte
				switch (evt.key.keysym.sym)
				{
				case SDLK_ESCAPE:	finished = TRUE;
					break;

				case SDLK_SPACE:
					if (autoPlayH) break;

					// FRONT MONTANT POUR H
					H = 1;					
					updateClock(pGSDL, E, H, &currentState, reset, states, &seq);					
					
					seqDisplay = seq;
					refresh = 1;

					break;
				case SDLK_LCTRL:
				case SDLK_RCTRL:
					// FRONT MONTANT POUR E					
					E = 1;					

					refresh = 1;
					break;
				case SDLK_BACKSPACE:

					// PASSAGE DE RESET A 1					
					reset = 1;
					updateClock(pGSDL, E, H, &currentState, reset, states, &seq);			

					refresh = 1;

					break;
				case SDLK_RETURN:
					// utilisation de la clock en automatique ou non
					autoPlayH = !autoPlayH;
					if (autoPlayH)
					{
						seqOffset = 0;
						// Pour changer le front d'horloge toutes les secondes
						tID = SDL_AddTimer(TIMER_DELAY, clockTimer, NULL);
					}
					else
					{
						SDL_RemoveTimer(tID);
					}
					refresh = 1;
					break;
				case SDLK_LEFT:
					// d�calage dans l'historique (� gauche)
					if (autoPlayH) break;

					seqOffset = -1;
					count = 0;
					refresh = 2;
					break;
				case SDLK_RIGHT:
					// d�calage dans l'historique (� droite)
					if (autoPlayH) break;

					seqOffset = 1;
					count = 0;
					refresh = 2;
					break;
				}

				break;
				// Touche clavier relach�e
			case SDL_KEYUP:
				// Si c'est ECHAP on quitte
				switch (evt.key.keysym.sym)
				{
				case SDLK_SPACE:
					if (autoPlayH) break;

					// FRONT DESCENDANT POUR H				
					H = 0;
					
					refresh = 1;

					break;
				case SDLK_LCTRL:
				case SDLK_RCTRL:
					// FRONT DESCENDANT POUR E					
					E = 0;
				
					refresh = 1;
					break;
				case SDLK_BACKSPACE:
					// FRONT DESCENDANT POUR RESET					
					reset = 0;
					
					refresh = 1;
					break;
				case SDLK_RIGHT:
				case SDLK_LEFT:
					seqOffset = 0;
					break;
				}

				break;
				// Croix en haut � droite de la fen�tre
			case SDL_QUIT:
				finished = TRUE;
				break;
			}

		}
		// On doit redessiner le graphe
		if (refresh)
		{			
			// On a boug� dans l'historique
			if (refresh == 2)
			{
				count++;

				if (count == 1 || count>50)
				{
					seqDisplay += seqOffset;
					seqDisplay = min(seq, seqDisplay);
					seqDisplay = max(1, seqDisplay);
					if (seq >= (RESX - 350 - OFFSETSEQ2) / 16) seqDisplay = max((RESX - 350 - OFFSETSEQ2) / 16, seqDisplay);
					else seqDisplay = seq;
				}
			}

			// On dessine le graphe
			if (!dessinerGraphe(pD, pGSDL, E, H, currentState, reset, states, seqDisplay, autoPlayH) || !refreshZoneDessin(pD)) finished = TRUE;
			if (refresh == 1) refresh = 0;
		}

		// On attend un peu pour ne pas surcharger le processeur en bouclant � l'infini
		SDL_Delay(10);
	}

	// On lib�re tout ce qui a �t� allouer (m�me le graphe contenu dans le graphe SDL
	if (!freeGrapheSDL(pGSDL)) return 0;
	if (!freeZoneDessin(pD)) return 0;

	// Retour
	return 1;
}
