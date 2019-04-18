#include "utils_SDL.h"

int main(int argc, char ** argv)
{
	SDL_Event e;
	SDL_Surface * window = NULL;
	SDL_Surface * heightmap = NULL;

	window = init("./data/heightmap.bmp", &heightmap, "Dijkstra");
	
	while (!interaction(&e))
	{
		update();

		draw(window, heightmap);
	}

	SDL_Quit();
	return EXIT_SUCCESS;
}
