#include "game.h"
				////////////////////////////////////////////////////
				///         FONCTIONS CONCERNANT LE JEU          ///
				////////////////////////////////////////////////////
/**
 *	@brief	Fonction permettant d'allouer et d'initialiser le jeu. 
 *	@param	p_size	Taille du plateau.
 *	@param	p_nbColor	Nombre de couleur utiliser pour la partie. 
 *	@return	Le jeu alloué et initialisé.
 */
game * CreateGame(unsigned char p_size, unsigned char p_nbColor)
{
	game * result = NULL;
	int i, j, size = p_size * p_size;
	float hue = 0;
	double proba;
	// TODO ...
	// 1. Allocation de la mémoire.

	result = (game*)calloc(1, sizeof(game));	
	result->m_board = (board*)calloc(1, sizeof(board));	
	result->m_reducedBoard = (board*)calloc(1, sizeof(board));
	result->m_colors = (color*)calloc(p_nbColor, sizeof(color));
	result->m_board->m_graph = (node**)calloc(p_size * p_size, sizeof(node*));		

	result->m_board->m_size = p_size * p_size;
	// 2. Initialisation des données et des voisins.

	result->m_size = p_size;
	result->m_nbColor = p_nbColor;
	result->m_nbMoves = 0;

	for (i = 0; i < p_nbColor; i++)
	{   // Création des p_nbColor couleurs souhaitées.
		result->m_colors[i] = CreateHSVColor(hue, 1.0f, 1.0f);
		hue = hue + (360 / p_nbColor);  // Découpage du cercle de couleurs selon le nombre de couleurs souhaitée.		
		result->m_colors[i] = HSV2RGB(result->m_colors[i]);  // On convertit les couleurs en RGB.
	}
	for (i = 0; i < p_size; i++)
	{  // Initialisation des voisins de chaques cases.
		for (j = 0; j < p_size; j++){
			result->m_board->m_graph[(j*p_size) + i] = (node*)calloc(1, sizeof(node));
			result->m_board->m_graph[(j*p_size) + i]->m_visited = 0;
			result->m_board->m_graph[(j*p_size) + i]->m_group = 0;				
			result->m_board->m_graph[i + j * p_size]->m_neighbours = NULL;			
		}
	}
	// Remplissage des couleurs de chaque cases avec une certaine probabilité d'avoir la même couleur que la case voisine.
	for (i = 0; i < p_size; i++)
	{
		for (j = 0; j < p_size; j++)
		{			
			proba = (rand() / (double)RAND_MAX);

			if (proba <= 0.50 && i > 0)	result->m_board->m_graph[(j*p_size) + i]->m_colorIndex = result->m_board->m_graph[(j*p_size) + (i - 1)]->m_colorIndex;

			else if (proba >= 0.70f && j > 0) result->m_board->m_graph[(j*p_size) + i]->m_colorIndex = result->m_board->m_graph[((j - 1)*p_size) + i]->m_colorIndex;

			else result->m_board->m_graph[(j*p_size) + i]->m_colorIndex = rand() % p_nbColor;
		}		
	}
	// Initialisation des voisins de chaques cases.
	for (i = 0; i < p_size; i++){  
		for (j = 0; j < p_size; j++){

			if ((j == 0 || j == p_size - 1) && (i == 0 || i == p_size - 1))  result->m_board->m_graph[(j*p_size) + i]->m_nbNeighbours = 2;  
																			   
			else if (j == 0 || j == p_size - 1 || i == 0 || i == p_size - 1) result->m_board->m_graph[(j*p_size) + i]->m_nbNeighbours = 3;  
																			   
			else result->m_board->m_graph[(j*p_size) + i]->m_nbNeighbours = 4;  

			if (i > 0)	result->m_board->m_graph[(j*p_size) + i]->m_neighbours = AddNodeList(result->m_board->m_graph[(j*p_size) + i]->m_neighbours, result->m_board->m_graph[(j*p_size) + (i - 1)]);  //voisin gauche

			if (j > 0) 	result->m_board->m_graph[(j*p_size) + i]->m_neighbours = AddNodeList(result->m_board->m_graph[(j*p_size) + i]->m_neighbours, result->m_board->m_graph[((j - 1)*p_size) + i]);  //voisin haut

			if (i < p_size - 1) result->m_board->m_graph[(j*p_size) + i]->m_neighbours = AddNodeList(result->m_board->m_graph[(j*p_size) + i]->m_neighbours, result->m_board->m_graph[(j*p_size) + (i + 1)]);  //voisin droit

			if (j < p_size - 1)	result->m_board->m_graph[(j*p_size) + i]->m_neighbours = AddNodeList(result->m_board->m_graph[(j*p_size) + i]->m_neighbours, result->m_board->m_graph[((j + 1)*p_size) + i]); //voisin bas
		}		
	}
	printf("0 Rouge\n1 Jaune\n2 Vert\n3 Cyan\n4 Marine\n5 Violet\n"); 
	return result;
}
/**
 *	@brief Fonction permettant de libérer le jeu.
 *	@param	p_game		Jeu à désallouer.
 */
void FreeGame(game * p_game)
{
	// TODO ...
	if (!p_game) return;
	FreeBoard(p_game->m_board);
	FreeBoard(p_game->m_reducedBoard);
	free(p_game->m_colors);
	free(p_game);
}
				////////////////////////////////////////////////////
				///        FONCTIONS CONCERNANT LE PLATEAU       ///
				////////////////////////////////////////////////////  
/**
 *	@brief	Fonction permettant de réduire un plateau.
 *			Le résultat est envoyé via un paramètre sortant passé par adresse qui est alloué dans la fonction (Attention aux fuites mémoires).
 *	@param	p_boardIn[IN]		Plateau à réduire.
 *	@param	p_boardOut[OUT]		Plateau réduit.
 */
int ReduceBoard(board * p_boardIn, board ** p_boardOut)
{
	// TODO ...	
	// 1. Recherche du nombre de noeud du graphe réduit
	
	unsigned int i, compteur = 0, k;
	for (i = 0; i < p_boardIn->m_size; i++)	p_boardIn->m_graph[i]->m_group = -1;	

	for (i = 0; i < p_boardIn->m_size; i++)
	{
		if (p_boardIn->m_graph[i]->m_group == -1) 
		{		
			list *voisin = NULL, *zone = NULL;
			p_boardIn->m_graph[i]->m_group = compteur;
			zone = AddNodeList(zone, p_boardIn->m_graph[i]);
			list* tmp = NULL;
			while (zone)
			{
				tmp = PopList(&zone);
				voisin = tmp->m_node->m_neighbours;
				while(voisin)
				{
					if (voisin->m_node->m_colorIndex == p_boardIn->m_graph[i]->m_colorIndex && voisin->m_node->m_group == -1)
					{
						voisin->m_node->m_group = compteur;
						zone = AddNodeList(zone, voisin->m_node);
					}
					voisin = voisin->m_next;
				}
				FreeList(tmp);			
			}
			compteur++;
		}
	}
	// 2. Création du graphe réduit
	
	board* reduit = (board*)calloc(1, sizeof(board));
	reduit->m_graph = (node**)calloc(compteur, sizeof(node*));
	reduit->m_size = compteur;	

	for (i = 0; i < compteur; i++) 
	{
		reduit->m_graph[i] = (node*)calloc(1, sizeof(node));
		reduit->m_graph[i]->m_group = i;
		reduit->m_graph[i]->m_visited = -1;
		reduit->m_graph[i]->m_neighbours = NULL;
		reduit->m_graph[i]->m_nbNeighbours = 0;
	}
	k = 0;
	// On associe les couleurs.
	for (i = 0; i < compteur; i++)		
	{
		while (p_boardIn->m_graph[k]->m_group != i)	k++;

		reduit->m_graph[i]->m_colorIndex = p_boardIn->m_graph[k]->m_colorIndex;
		k = 0;
	}
	for (i = 0; i < p_boardIn->m_size; i++) 
	{
		list* tmp = p_boardIn->m_graph[i]->m_neighbours;

		while (tmp) 
		{
			if ((tmp->m_node->m_group != p_boardIn->m_graph[i]->m_group) && !IsNeighbours(reduit->m_graph[tmp->m_node->m_group], reduit->m_graph[p_boardIn->m_graph[i]->m_group]))
			{
				reduit->m_graph[p_boardIn->m_graph[i]->m_group]->m_neighbours = AddNodeList(reduit->m_graph[p_boardIn->m_graph[i]->m_group]->m_neighbours, reduit->m_graph[tmp->m_node->m_group]);			
				reduit->m_graph[tmp->m_node->m_group]->m_neighbours = AddNodeList(reduit->m_graph[tmp->m_node->m_group]->m_neighbours, reduit->m_graph[p_boardIn->m_graph[i]->m_group]);
				
				reduit->m_graph[p_boardIn->m_graph[i]->m_group]->m_nbNeighbours++;
				reduit->m_graph[tmp->m_node->m_group]->m_nbNeighbours++;
			}
			tmp = tmp->m_next;
		}
	}
	if(*p_boardOut)	FreeBoard(*p_boardOut);
	*p_boardOut = reduit;	

	return 1;
}
/**
 *	@brief	Fonction permettant de copier un plateau.
 *
 *	@param	p_board			Plateau à copier.
 *
 *	@return	Le plateau copié
 */
board * CopyBoard(board * p_board)
{
	board * result = NULL;
	int voisinindex = 0;
	unsigned int i;

	result = (board*)calloc(1, sizeof(board));
	result->m_size = p_board->m_size;
	result->m_graph = (node**)calloc(result->m_size, sizeof(node*));

	for (i = 0; i < p_board->m_size; i++){
		result->m_graph[i] = (node*)malloc(sizeof(node));
		result->m_graph[i]->m_neighbours = (list*)malloc(sizeof(list));
		result->m_graph[i]->m_colorIndex = p_board->m_graph[i]->m_colorIndex;
		result->m_graph[i]->m_neighbours = NULL;
		result->m_graph[i]->m_nbNeighbours = p_board->m_graph[i]->m_nbNeighbours;
		result->m_graph[i]->m_visited = p_board->m_graph[i]->m_visited;
		result->m_graph[i]->m_index = i;
	}
	for (i = 0; i < p_board->m_size; i++)
	{ // Lier les voisins.
		
		list * tmp = p_board->m_graph[i]->m_neighbours;
		while (tmp){
			voisinindex = tmp->m_node->m_index;
			result->m_graph[i]->m_neighbours = AddNodeList(result->m_graph[i]->m_neighbours, result->m_graph[voisinindex]);
			tmp = tmp->m_next;
		}
	}
	return result;
}
/**
 *	@brief	Fonction permettant de comparer deux plateaux.
 *
 *	@return	1 si les plateau sont identiques,
 *			0 sinon.
 */
int SameBoards(board * p_board1, board * p_board2){
	// TODO ...	
	if (!p_board1 || !p_board2 || (p_board1->m_size != p_board2->m_size)) return 0;

	for (unsigned int i = 0; i < p_board1->m_size; i++) 
	{
		if (p_board1->m_graph[i]->m_colorIndex != p_board2->m_graph[i]->m_colorIndex) return 0;
		if (p_board1->m_graph[i]->m_nbNeighbours != p_board2->m_graph[i]->m_nbNeighbours) return 0;
		if (p_board1->m_graph[i]->m_visited != p_board2->m_graph[i]->m_visited) return 0;
	}	
	return 1;
}
/**
 *	@brief	Fonction permettant d'appliquer une couleur au plateau.
 *
 *	@param	p_board			Pointeur sur le plateau.
 *	@param	p_colorIndex	Couleur à appliquer sur le plateau.
 */
void ApplyColor(board ** p_board, unsigned char p_colorIndex){
	
	// TODO ...
	unsigned int i;
	char j;
	list *tmp = NULL;
	(*p_board)->m_graph[0]->m_visited = 1;

	for (i = 0; i < (*p_board)->m_size; i++)
	{  // On parcourt toutes les cases du tableau.
		// Variable temporaire contenant la liste des voisins de la case en cours.
		tmp = (*p_board)->m_graph[i]->m_neighbours;   
		 // Si le voisin de la case en cours à la même couleur que celle qui a été jouée
		 // Et que la case à déjà été visitée, alors ce voisin est marqué comme visité.
		for (j = 0; j < (*p_board)->m_graph[i]->m_nbNeighbours; j++)
		{		
			if (p_colorIndex == tmp->m_node->m_colorIndex && (*p_board)->m_graph[i]->m_visited == 1)  tmp->m_node->m_visited = 1;  			
			tmp = tmp->m_next;  
		}
		// Chaque noeud déjà visité prend la couleur en cours.
		if ((*p_board)->m_graph[i]->m_visited == 1) (*p_board)->m_graph[i]->m_colorIndex = p_colorIndex;		
	}
}
/**
 *	@brief	Fonction permettant de savoir si le plateau est fini.
 *			La fonction se basera sur un plateau réduit.
 *
 *	@param	p_board			Plateau réduit.
 *
 *	@return	1 si le plateau est fini
 *			0 sinon
 */
int IsFinished(board * p_board) 
{
	// TODO ...
	char test = p_board->m_graph[0]->m_colorIndex;

	for (unsigned int i = 0; i < p_board->m_size; i++)
		if (p_board->m_graph[i]->m_colorIndex != test)
			return 0;
	return 1;
}
/**
 *	@brief	Fonction permettant de libérer un plateau.
 *
 *	@param	p_board		Plateau à désallouer.
 */
void FreeBoard(board * p_board)
{
	// TODO ...	
	if (!p_board) return;
	FreeGraph(p_board->m_graph, p_board->m_size);
	free(p_board);	
}
				////////////////////////////////////////////////////
				///        FONCTIONS CONCERNANT LE GRAPHE        ///
				////////////////////////////////////////////////////
/**
 *	@brief	Fonction permettant de vérifier si deux noeuds de graphe sont voisins.
 *
 *	@return	1 si les noeuds sont voisins,
 *			0 sinon.
 */

int IsNeighbours(node * p_node1, node *p_node2)
{
	// TODO ...	
	if (!p_node1->m_neighbours || !p_node2->m_neighbours)	return 0;
	list *tmp = p_node1->m_neighbours;	

	for (char i = 0; i < p_node1->m_nbNeighbours; i++)
	{
		if (tmp->m_node == p_node2)	return 1;		
		tmp = tmp->m_next;
	}
	return 0;
}
/**
 *	@brief	Fonction permettant de libérer un graphe.
 *
 *	@param	p_graph		Graphe à désallouer.
 */
void FreeGraph(node ** p_graph, unsigned int p_size)
{
	// TODO ...	
	if (!p_graph) return;
	for (unsigned int i = 0; i < p_size; i++)
	{
		FreeList(p_graph[i]->m_neighbours);
		free(p_graph[i]);
	}
	free(p_graph);
}
				////////////////////////////////////////////////////
				/// FONCTIONS CONCERNANT LES LISTES D'ADJACENCES ///
				////////////////////////////////////////////////////
/**
 *	@brief	Fonction permettant d'ajouter un noeud à une liste d'adjacence (Fonction récursive).
 *
 *	@param	p_list		Liste d'adjacence.
 *	@param	p_node		Noeud de liste à ajouter.
 *
 *	@return	liste d'adjacence modifier.
 */
list * AddNodeList(list * p_list, node * p_node)
{
	if (!p_list)
	{
		list * newNode = (list *)malloc(sizeof(list));
		newNode->m_next = NULL;
		newNode->m_node = p_node;
		return newNode;
	}
	p_list->m_next = AddNodeList(p_list->m_next, p_node);
	return p_list;
}
/**
 *	@brief	Fonction permettant de récupérer la tête de la liste d'adjacence.
 *
 *	@param	p_list		Pointeur sur la liste d'adjacence.
 *
 *	@return Pointeur sur le noeud de liste extrait.
 */
list * PopList(list ** p_list){
	list * result = NULL;

	if (!p_list || !*p_list)	return NULL;

	result = *p_list;
	*p_list = (*p_list)->m_next;
	result->m_next = NULL;

	return result;
}
/**
 *	@brief	Fonction permettant de libérer une liste d'adjacence.
 *
 *	@param	p_list		Liste d'adjacence à désallouer.
 */
void FreeList(list * p_list)
{
	if (!p_list) return;

	if (p_list->m_next)	FreeList(p_list->m_next);

	free(p_list);
}