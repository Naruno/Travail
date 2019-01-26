#include "utilSDL.h"
#include "Timer.h"
#include "vector.h"
#include "obj.h"
#include "Firework.h"
#include <time.h>

#ifdef _DEBUG
// to print the state in debug mode
#define _VERBOSE_
#endif

// number of fireworks to generate simultaneously
#define NB_FIREWORKS	1

// maximum number of objects
#define MAX_OBJECTS		10

// OPENGLJOB
// do the openGL job
// RETURN : /
// width : width of the window 
// height : height of the window 
// angleX : orientation of the world regarding X axis
// angleY : orientation of the world regarding Y axis
// zoomValue : distance between camera & center of the world
void openGLJob(int width, int height, float angleX, float angleY, float zoomValue);

// OPENGLDISPLAY
// To display the rendering on screen
// RETURN : /
void openGLDisplay();

// SDLJOB
// Do the SDL event management job 
// Create the window at first call : the window is created at desktop resolution (/2 in debug mode)
// bRunning : is the program should continue to run
// pLines : pointer on a "boolean" value to know if we must draw or not the lines between the firework particles
// pMatrix : pointer on a "boolean" value to know if we are running in "matrix-like" mode
// pG : pointer on gravity vector to modify it regarding the world orientation if needed
int SDLJob( int bRunning, int * pLines, int * pMatrix, vector3D * pG);

// OPENGLJOB
// do the openGL job
// RETURN : /
// width : width of the window 
// height : height of the window 
// angleX : orientation of the world regarding X axis
// angleY : orientation of the world regarding Y axis
// zoomValue : distance between camera & center of the world
void openGLJob(int width, int height, float angleX, float angleY, float zoomValue)
{
	// clear the buffers to draw into
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// screen projection
	{
		// screen ratio
		double ratio = width/(double)height;
		// clipping planes
		double nearPlane,farPlane;
		nearPlane = max(0.001,zoomValue-100.0f);
		farPlane =	max(100.0, zoomValue+100.0f);

		// Configure matrix mode to set the projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Projection matrix
		glFrustum(-0.75*ratio*nearPlane,0.75*ratio*nearPlane,-0.75*nearPlane,0.75*nearPlane, nearPlane , farPlane );
	}

	// Light & navigation
	{
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		// Navigate before drawing
		glTranslated(0.0,0.0,-zoomValue);
		glRotated(angleX,1.0,0.0,0.0);
		glRotated(angleY,0.0,1.0,0.0);
	}

}

// OPENGLDISPLAY
// To display the rendering on screen
// RETURN : /
void openGLDisplay()
{
	// swap buffers to display the rendering at screen
	SDL_GL_SwapBuffers();
}


// SDLJOB
// Do the SDL event management job 
// Create the window at first call : the window is created at desktop resolution (/2 in debug mode)
// bRunning : is the program should continue to run
// pLines : pointer on a "boolean" value to know if we must draw or not the lines between the firework particles
// pMatrix : pointer on a "boolean" value to know if we are running in "matrix-like" mode
// pG : pointer on gravity vector to modify it regarding the world orientation if needed
int SDLJob( int bRunning, int * pLines, int * pMatrix, vector3D * pG)
{
	static int firstCall = 1;
	// Window pointer
	SDL_Surface * pWindow = NULL;
	// Fullscreen mode ?
	static int fullscreen = 1;
	// window size
	static int width, height;
	// shift state
	static int lShift = 0;
	// drag&drop state
	static int dragAndDrop = 0;
	// zoom state
	static int zoom = 0;
	// navigation data state
	static float angleX = 0.0f;
	static float angleY = 0.0f;
	static float zoomValue = 10.0f;
	// SDL event to get the message from keyboard/mouse/window
	SDL_Event event;
	
	// if we ask the window to close (bRunning = 0) and the window has already been created, close everything !
	if(!bRunning && !firstCall && pWindow)
	{
		SDL_FreeSurface(pWindow);
		return 0;
	}

	// if it is the first call create the window
	if(firstCall)
	{
		
	// get the screen resolution
		width = GetSystemMetrics(SM_CXSCREEN);
		height = max(GetSystemMetrics(SM_CYSCREEN),1);
	#ifdef _DEBUG
		// if DEBUG mode : windowed with half resolution
		fullscreen = 0;
		width = max(1,width/2);
		height = max(1,height/2);
	#endif

		// window creation
		pWindow = initGLWindow(width,height,"Firework 3D",fullscreen);
		if(!pWindow) return 0;

		firstCall = 0;

		return 1;
	}

	// messages management
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			// Click on the quit button (the top left cross) on the window toolbar
			case SDL_QUIT:
				bRunning = 0;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					// quit
					case SDLK_ESCAPE:
						bRunning = 0;
						break;
						// display lines
					case SDLK_SPACE:
						*pLines = !*pLines;				
						break;
						// matrix mode
					case SDLK_PAUSE:
						*pMatrix = !*pMatrix;
						break;
				}
				break;
			// mouse button pressed
			// zoom/rotation activated
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT && !zoom) 
					dragAndDrop++;
				if(event.button.button == SDL_BUTTON_RIGHT && ! dragAndDrop) 
					zoom++;
				break;
			// mouse button released
			// zoom/rotation deactivated
			case SDL_MOUSEBUTTONUP:
				if (dragAndDrop && event.button.button == SDL_BUTTON_LEFT) 
					dragAndDrop--;
				if(zoom && event.button.button == SDL_BUTTON_RIGHT) 
					zoom--;
				break;
			// mouse moved
			// zoom/rotation updated
			case SDL_MOUSEMOTION:
				if(dragAndDrop)		
				{
					angleX += event.motion.yrel/3.0f;
					angleY += event.motion.xrel/3.0f;	
				}
				if(zoom)
				{
					zoomValue += event.motion.yrel/50.0f;

				}
				break;
		} 
	} 

	// rotation value around X axis limited : -180/180
	if(angleX<-180.0f)	angleX=-180.0f;
	if(angleX>180.0f)	angleX=180.0f;	
	// rotation value around Y axis limited : 0/360
	if(angleY<0.0f)		angleY+=360.0f;
	if(angleY>360.0f)	angleY-=360.0f;
	// zoom value limited : 0.1/40.0
	if(zoomValue<0.1f)	zoomValue=0.1f;
	if(zoomValue>40.0f)	zoomValue=40.0f;

	// Do the opengl Job
	openGLJob(width,height,angleX, angleY, zoomValue);

	// use the angles to modify gravity if needed
	{
		double xRadian = angleX*M_PI/180.0f;
		double yRadian = angleY*M_PI/180.0f;
	}

#ifdef _VERBOSE_
	// Debug display if _VERBOSE_ is defined
		printf(" [% 5.2lf][% 6.1lf;% 6.1lf] - Matrix [%s] - Lines [%s]                ",zoomValue, angleX, angleY, *pMatrix?"ON ":"OFF",*pLines?"ON ":"OFF");
#endif	
	return bRunning;
}

// MAIN PROGRAM
int main( int argc, char** argv )
{
	// when should we stop the running loop ? when bRunning is equals to 0
	int bRunning = 1; 
	// Should we draw the lines ?
	int bLines = 0;
	// Should we use slowMotion as in Matrix movie?
	int bMatrix = 0;
	// timer to store the time elapsed between 2 frames
	timer t;
	
	// FIREWORK declaration
	Firework f[NB_FIREWORKS];

	// gravity vector calculated regarding the view orientation
	vector3D gravity;
	
	// complex objects to display
	object o[MAX_OBJECTS];
	// number of objects loaded
	int nbObjects = 0;

	// pos & size of the complex object 
	vector3D pos = {0.0,0.0,0.0};
	vector3D size = {1.0,1.0,1.0};

	// should object be displayed ?
	int displayObj = 0;

	// counter
	int i;


	// initialize gravity vector
	SETVECTOR3D(gravity, 0.0,-1.0 , 0.0 );

	// initialize the random number generation seed
	srand((unsigned)time(NULL));

	// initialize the fireworks 
	// TODO
	{
		for (i = 0; i < NB_FIREWORKS; i++) {
			create_Firework((f + i));			
		}
	}
	
	
	

	// first call to the SDLJob function to create the window
	bRunning = SDLJob(bRunning, &bLines, &bMatrix,&gravity);

	// Load the complex objects from OBJ files (you MUST do this after having created the window in order to be able to load potential texture)
	if(argc>1) 
	{
		for(i=1; i < argc && nbObjects<MAX_OBJECTS; i++)
		{
			displayObj = loadObjFromFile(argv[i],&o[i-1]);
			if(displayObj) nbObjects++;
		}

#ifdef _VERBOSE_
		if(nbObjects==MAX_OBJECTS && i < argc)
		{
			printf("\nWarning : Two many objects. Only [%d] objects are loaded by this program.\n\n",MAX_OBJECTS);
		}
#endif

		if(nbObjects>0) displayObj = 1;

		// ground object bounding box
		if(displayObj)
		{
			// update bouding box of the first object (ground object for us) in order to prevent the particles of the fireworks to go throught the floor
			vector3D ground;
			SETVECTOR3D(ground,0,-1,0);
			UPDATEBBOX(o[0].boundingBox,ground);
		}
	}

	// main loop 
	while(bRunning)
	{

		// get time elapsed since last frame
		frame(&t);

#ifdef _VERBOSE_
	// Debug display if _VERBOSE_ is defined
		printf("\rFPS [% 4d] -",(int)(1.0/t.deltaTime));
#endif	

		// Do the SDL event management job ...
		bRunning = SDLJob(bRunning, &bLines, &bMatrix,&gravity);
		
		//  DRAWING
		// draw the objects
		if(displayObj) 
		{
			for(i=0; i < nbObjects; i++)
			{
				drawObjPosSize(&o[i],pos,size);
			}
		}

		// update & draw the fireworks
		{
			for (i = 0; i < NB_FIREWORKS; i++) {
				update_Firework(&((f + i)->p_particule), t.deltaTime, 0, (f + i)->nb_level);
				vector3D pos;
				pos.x = (f + i)->position[X];
				pos.y = (f + i)->position[Y];
				pos.z = (f + i)->position[Z];
				color rgb;
				rgb.color[0] = (f + i)->p_particule->color[0];
				rgb.color[1] = (f + i)->p_particule->color[1];
				rgb.color[2] = (f + i)->p_particule->color[2];

				drawSphere(pos, (f + i)->p_particule->size, rgb);
			}
		}


		//display the rendering on screen
		openGLDisplay();


	}
	
	// TODO


	// free the object if needed
	if(displayObj) 
	{
		for(i=0; i < nbObjects; i++)
		{
			freeObj(&o[i]);
		}
	}

	return EXIT_SUCCESS;
}