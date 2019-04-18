#include "aStar.h"

/**
*	@brief	Fonction permettant de créer (allouer) un noeud de liste utilisée pour A*.
*
*	@param	p_board		Plateau réduit du jeu.
*	@param	p_g			Distance déjà parcourue entre l'état initial et l'état courant
*	@param	p_f			Evaluation de la distance à parcourir entre l'état initial et l'état final (g + h).
*	@param	p_color		Dernière couleur appliquée pour arriver à ce plateau.
*	@param	p_prev		Pointeur vers le noeud correspondant au plateau précédent dans la solution.
*
*	@return	Le noeud de liste alloué et initialisé.
*/
aStar * CreateNodeAStar(board * p_board, int p_g, int p_f, unsigned int p_color, aStar * p_prev)
{
	aStar * result = NULL;
	// TODO ...
	result = (aStar*)calloc(1, sizeof(aStar));

	result->m_color = p_color;
	result->m_g = p_g;
	result->m_f = p_f;
	result->m_board = p_board;
	result->m_prev = p_prev;
	result->m_next = NULL;
	return result;
}

/**
*	@brief	Fonction permettant d'insérer un noeud dans un liste de manière triée ou non.
*
*	@param	p_list		Liste utilisée pour A*.
*	@param	p_node		Noeud à insérer dans la liste.
*	@param	p_tri		1 si l'insertion doit se faire de manière triée, 0 sinon.
*/
void InsertNodeAStar(aStar ** p_list, aStar * p_node, int p_tri)
{
	// TODO ...
	if (!p_list || !p_node)	return;

	if (!p_tri || !(*p_list) || p_node->m_f <= (*p_list)->m_f)  		
	{ // Insertion non triée ou au bon endroit.
		p_node->m_next = (*p_list);
		(*p_list) = p_node;
		return;
	} // Cas de l'insertion triée.
	InsertNodeAStar(&(*p_list)->m_next, p_node, p_tri); 
}
/**
*	@brief	Fonction permettant de récupérer la tête d'une liste utilisée pour A*.
*
*	@param	p_list		Pointeur sur la liste pour A*.
*
*	@return Pointeur sur le noeud de liste extrait.
*/
aStar * PopListAStar(aStar ** p_list)
{
	aStar * result = NULL;	
	// TODO ...
	if (!p_list || !(*p_list))	return NULL;

	result = (*p_list);
	// Si le premier noeud a un successeur.
	// Alors le premier noeud devient ce successeur.
	if ((*p_list)->m_next)	(*p_list) = (*p_list)->m_next;		
	
	// Sinon, le contenu de liste devient NULL.
	else   (*p_list) = NULL;			

	result->m_next = NULL;
	return result;
}

/**
*	@brief	Fonction permettant de savoir si un plateau se trouve dans une liste A*.
*
*	@param	p_list		Liste A*.
*	@param	p_board		Plateau à chercher.
*
*	@return Noeud dans lequel on trouve le plateau passé en paramètre (pointeur sur le pointeur dans la liste).
*/
aStar ** IsInList(aStar ** p_list, board * p_board)
{
	// TODO ...
	aStar ** tmp = p_list;

	if (!p_list || !(*p_list) || !p_board)	return NULL;
	// Tant que le board de p_list n'est pas celui cherché ou qu'on est pas a la fin.
	while (!SameBoards((*tmp)->m_board, p_board) && (*tmp)->m_next)	 tmp = &((*tmp)->m_next);

	if (SameBoards((*tmp)->m_board, p_board))	return tmp;
	// A la fin de la liste.
	else return NULL;
}
/**
*	@brief	Fonction de résolution du jeu en utilisant l'algorithme A*.
*
*	@param	p_board				Plateau à résoudre (plateau réduit).
*	@param	p_colors[OUT]		Tableau des couleurs de la solution.
*	@param	p_nbColors[OUT]		Nombre de couleurs dans la solution.
*
*	@return	 1	si le plateau a été résolu,
*			-1	si une erreur est sruvenue,
*			 0	sinon.
*/

 
int SolveGame(board * p_board, unsigned int ** p_colors, unsigned int * p_nbColors, unsigned int nbcouleur)
{ // Ne marche pas ;_;
	/// TODO ...
	printf("\nASTAR %d couleurs \n", nbcouleur);

	if (!p_board)	return -1;

	unsigned int i, compteur = 0;
	aStar *jeu = CreateNodeAStar(p_board, 0, 0, p_board->m_graph[0]->m_colorIndex, NULL), *visitee = NULL, *courrant = NULL;

	(*p_nbColors) = 0;

	// Tant que le jeu n'est pas fini.
	while (jeu)
	{
		courrant = PopListAStar(&jeu);
		// Si on a plus qu'une seule couleur a jouer.
		if (H(courrant->m_board) == 1) break;
		// Pour toutes les couleurs.

		for (i = 0; i < nbcouleur; i++)	// Représente tous les voisins possibles.
		{ // Sauf l'actuelle.
			if (i == courrant->m_color) continue;
			// On crée le board correspondant.	
			aStar * tempo = NULL;
			board * copy = CopyBoard(courrant->m_board);

			ApplyColor(&copy, i);
			
			if (IsInList(&visitee, copy))	continue;

			// On calcul le F du board = on crée le noeud.
			tempo = CreateNodeAStar(copy, courrant->m_g + 1, courrant->m_g + 1 + H(copy), i, courrant);			

			// Si est dans jeu.
			aStar ** test = IsInList(&jeu, tempo->m_board);
			if (test)
			{				
				if ((*test)->m_f < tempo->m_f)	continue;
				
				else
				{
					aStar* exemple = (*test)->m_next;
					(*test) = exemple;
				}
			}
			// On insère le board dans jeu.
			InsertNodeAStar(&jeu, tempo, 1);
		}
		// On ajoute le noeud 1, le plus intéressant dans la liste des déjà vus. 
		InsertNodeAStar(&visitee, courrant, 0);
	}

	// Supprimer le dernier de la boucle. 
	aStar *value = courrant, *tmp = courrant;

	// On compte le nombres de coups dont on a besoin.
	while (tmp->m_prev) 
	{
		(*p_nbColors)++;
		tmp = tmp->m_prev;
	}
	// On alloue le tableau donnant les couleurs requises.
	*p_colors = (unsigned int*)malloc((*p_nbColors) * sizeof(unsigned int)); 
	int countcol = (*p_nbColors);
	tmp = courrant;
	while (tmp->m_prev)
	{
		(*p_colors)[countcol - 1] = tmp->m_color;
		countcol--;
		tmp = tmp->m_prev;
	}
	printf("A* fini\n");

	free(jeu);
	free(visitee);
	return 0;
}

int comptage(aStar * list)
{
	if (list == NULL)
		return 0;
	int compteur = 0;
	aStar *temp = list;
	while (temp)
	{
		compteur++;
		temp = temp->m_next;
	}
	return compteur;

}


/**
*	@brief	Fonction de calcul de l'heuristique pour l'algorithme A*.
*
*	@param	p_board			Plateau du jeu.
*
*	@return	Valeur de l'heuristique.
*/
int H(board * p_board)
{
	// TODO ...
	// Tableau marquant les couleurs visitées.
	unsigned int *tabcolor = (unsigned int *)calloc(p_board->m_size, sizeof(unsigned int)), res = 0, i; 

	for (i = 0; i < p_board->m_size; i++)
	{ // Si la couleur vu n'a pas encore été marquée.
		if (!(tabcolor[p_board->m_graph[i]->m_colorIndex])) 
		{// On note la couleur visitée.
			tabcolor[p_board->m_graph[i]->m_colorIndex] = 1; 
			res++;
		}
	}
	free(tabcolor);
	return res;
}