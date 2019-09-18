#include "simu.h"
#include "tissu.h"


#define WIDTH	10
#define LENGTH	10

#define SIZE_W	0.5f
#define SIZE_L	0.5f

#define NB_OBSTACLES 1


/*! variable to store the current camera position */
vec3	g_navPos;
/*! variable to store the current camera orientation (Euler angles) */
vec3	g_navOrientation;
/*! to know if we are using the mouse in order to navigate */
bool	g_mouseNavigation = FALSE;
/*! to know if we are using the mouse to change the position of the camera */
bool	g_mouseTranslation = FALSE;

/*! list of particles organized in a 2D array */
particle **g_arrayOfParticles = NULL;

/*! list of obstacles */
obstacle g_obstacles[NB_OBSTACLES];

/*! coefficient to manage the time (make slow motion for instance or pause the simulation */
float g_timeCoef = 1.0f;


/*!
 *	\brief to initialize the simulation & the rendering
 */
void init()
{
	int i = 0;
	int j = 0;

	 /* Clear our buffer with a black background */
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClearDepth( 1.0f );

	//initialize the OpenGL States
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

	glEnable( GL_COLOR_MATERIAL );

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum( -0.01 , 0.01 , -0.01 , 0.01 , 0.01 , 10.0 );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* initialize the position & orientation of the camera */
	g_navPos = set3( 0.0f , -0.5f , -1.0f );
	g_navOrientation = set3( 0.0f , 0.0f , 0.0f );

	/* initialize the particles' array */
	g_arrayOfParticles = createFabric(SIZE_W,SIZE_L,WIDTH,LENGTH, g_obstacles, NB_OBSTACLES);


}

/*!
 *	\brief	to process the render loop
 *
 *	\param p_window	the handle of the window in which the rendering will be done
 */
void renderLoop(SDL_Window * p_window)
{
	Uint32 t = SDL_GetTicks();
	Uint32 t_dt = t;
	float dt = 0.0f;

	//initialize the simulation & the rendering
	init();

	if(!g_arrayOfParticles)
		return;

	while(!events())
	{
		//Calculate time elapsed
		t_dt = SDL_GetTicks();
		dt = (t_dt-t)/1000.0f;
		t = t_dt;

		// update the simulation
		update( dt*(g_timeCoef>0.0f?g_timeCoef:0.0f) );

		// render the scene
		render();

		/* Swap our back buffer to the front : display in the window */
		SDL_GL_SwapWindow(p_window);

		/* Let processor time to other processes */
		SDL_Delay(0);
	}

	/* delete the particles used to simulate fabric */
	deleteFabric(g_arrayOfParticles,WIDTH,LENGTH);
}
	

/*!
 *	\brief to manage the events
 *
 *	\return		1 if application should quit, 0 else
 */
bool events()
{
	// EVENTS ---------------------------------------------------------------------
	int i, j;
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			case SDL_QUIT:
				return TRUE;
				break;
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						return TRUE;
					case SDLK_p:
						g_timeCoef = -g_timeCoef;
						break;
					case SDLK_SPACE:
						for (i = 0; i < WIDTH; i++) {
							for (j = 0; j < LENGTH; j++) {
								free(g_arrayOfParticles[i][j].m_voisinage);
							}
							
						}
						initializeArrayOfParticles(g_arrayOfParticles, SIZE_W,SIZE_L, WIDTH, LENGTH, g_obstacles, 0);
						break;
					case SDLK_KP_PLUS:
							g_timeCoef = min(1.0f,g_timeCoef*2.0f);
							break;
					case SDLK_KP_MINUS:
							g_timeCoef = g_timeCoef/2.0f;
							break;
					default:
						break;
				}
				
				break;
			case SDL_KEYUP:
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(e.button.button == SDL_BUTTON_LEFT)
					g_mouseNavigation = TRUE;
				else
					g_mouseTranslation = TRUE;
				break;
			case SDL_MOUSEBUTTONUP:
				if(e.button.button == SDL_BUTTON_LEFT)
					g_mouseNavigation = FALSE;
				else
					g_mouseTranslation = FALSE;
				break;
			case SDL_MOUSEMOTION:
				if(g_mouseNavigation)
					g_navOrientation = add3(g_navOrientation, set3(e.motion.yrel/10.f,(float)e.motion.xrel,0.0f));
				if(g_mouseTranslation)
					g_navPos = add3( g_navPos , set3(e.motion.xrel/100.0f,-e.motion.yrel/100.0f,0.0f) ); 
				break;
			case SDL_MOUSEWHEEL:
				g_navPos = add3( g_navPos , set3(0.0f,0.0f,e.wheel.y/100.0f));
				break;
			default:
				break;
		}
	}

	return FALSE;
}

/*!
 *	\brief	to update the simulation
 *
 *	\param p_dt time elapsed since last call
 */
void update(float p_dt)
{
	updateFabric(g_arrayOfParticles,WIDTH,LENGTH,p_dt,g_obstacles,NB_OBSTACLES);
}

/*! 
 *	\brief do the rendering of the scene
 */
void render()
{
	GLfloat pos[4] = {0.0f,0.0f,0.0f,1.0f};

	// RENDERING ------------------------------------------------------------------
	/* Clear the rendering */
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//navigate
	glLoadIdentity();

	glLightfv(GL_LIGHT0,GL_POSITION,pos);

	glTranslatef(g_navPos.x,g_navPos.y,g_navPos.z);
	glRotatef(g_navOrientation.x,1.0f,0.0f,0.0f);		
	glRotatef(g_navOrientation.y,0.0f,1.0f,0.0f);

	glRotatef(g_navOrientation.z,0.0f,0.0f,1.0f);
	
#ifdef _DEBUG
	drawRef();
#endif

	// draw the fabric
	drawFabric(g_arrayOfParticles,WIDTH,LENGTH, g_obstacles,NB_OBSTACLES);


}
