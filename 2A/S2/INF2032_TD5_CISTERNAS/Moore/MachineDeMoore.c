#include "tools.h"
#include "grapheSDL.h"

int main(int argc, char ** argv){
	// Initialisation
	pGraphe graphe = NULL;

#ifdef _DEBUG
	// Detection fuites memoire
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	// Creation du graphe
	graphe = creerGraphe();

	if (graphe){
		// Boucle de rendu SDL
		renderLoop(graphe);
	}
	// Retour
	return 0;
}