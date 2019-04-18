#include "gameSDL.h"
#include "aStar.h"
#include "vld.h"

#define	BOARD_SIZE	20
#define	RESOLUTION	20

int main(int argc, char ** argv)
{
	int end = 0;
	gameSDL * g;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER))
	{
		system("pause");
		return EXIT_FAILURE;
	}

	srand((unsigned int)time(NULL));

	g = CreateGameSDL(BOARD_SIZE, RESOLUTION, NB_MAX_COLOR);
	DrawGameSDL(g);

	while (!end)
	{
		SDL_Event e;

		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_KEYUP:
					switch (e.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							end = 1;
							break;

						case SDLK_SPACE:
							ReloadGameSDL(&g);
							DrawGameSDL(g);
							break;

						case SDLK_RETURN:
						case SDLK_KP_ENTER:
							if (g->m_game)
							{
								board * b = (board *)calloc(1, sizeof(board));
								unsigned int *colors, nbColor;

								printf("Recherche en cours ...\n");
								
								ReduceBoard(g->m_game->m_board, &(g->m_game->m_reducedBoard));
								SolveGame(g->m_game->m_reducedBoard, &colors, &nbColor, g->m_game->m_nbColor);

								for (unsigned int i = 0; i < nbColor; i++)
								{
									ApplyColor(&g->m_game->m_board, colors[i]);
									DrawGameSDL(g);
								}

								free(colors);
							}
							break;
					}
					break;

				case SDL_KEYDOWN:
					switch (e.key.keysym.sym)
					{
						case SDLK_KP0:
						case SDLK_KP1:
						case SDLK_KP2:
						case SDLK_KP3:
						case SDLK_KP4:
						case SDLK_KP5:
						case SDLK_KP6:
						case SDLK_KP7:
						case SDLK_KP8:
						case SDLK_KP9:
							if (g->m_game)
							{
								int choice = e.key.keysym.sym - SDLK_KP0;

								if (choice >= 0 && choice<g->m_game->m_nbColor)
								{
									ApplyColor(&(g->m_game->m_board), choice);
									ReduceBoard(g->m_game->m_board, &g->m_game->m_reducedBoard);
									g->m_game->m_nbMoves++;
								}

								if (IsFinished(g->m_game->m_reducedBoard))
									printf("gagne en %d mouvements !\n", g->m_game->m_nbMoves);
								DrawGameSDL(g);
							}
							break;

						case SDLK_0:
						case SDLK_1:
						case SDLK_2:
						case SDLK_3:
						case SDLK_4:
						case SDLK_5:
						case SDLK_6:
						case SDLK_7:
						case SDLK_8:
						case SDLK_9:
							if (g->m_game)
							{
								int choice = e.key.keysym.sym - SDLK_0;

								if (choice >= 0 && choice < g->m_game->m_nbColor)
								{
									ApplyColor(&(g->m_game->m_board), choice);
									ReduceBoard(g->m_game->m_board, &g->m_game->m_reducedBoard);
									g->m_game->m_nbMoves++;
								}
								if (IsFinished(g->m_game->m_reducedBoard))
								 printf("gagne en %d mouvements !\n", g->m_game->m_nbMoves);
									
								DrawGameSDL(g);
							}
							break;
						default:
							break;
					}
					break;

				case SDL_QUIT:
					end = 1;
					break;

				default:
					break;
			}
		}
		SDL_Delay(1);
	}
	FreeGameSDL(g);
	
	return EXIT_SUCCESS;
}