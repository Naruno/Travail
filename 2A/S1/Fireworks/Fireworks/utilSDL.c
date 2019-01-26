#include "utilSDL.h"
#include "../Librairies/SDL-1.2.15/include/SDL.h"
#include <Windows.h>
#include <GL/GL.h>
#include "Firework.h"
// To use M_PI #define
#define _USE_MATH_DEFINES
#include <math.h>

// INITGLWINDOW
// to create the OpenGL Window at width x height resolution with its title in fullscreen or not
// RETURN : the pointer on the SDL_Surface used to draw in the window
// width : width of the window
// height : height of the window
// title : title of the window
// fullscreen : "boolean" value to set the window in fullscreen (!=0) or not (0)
SDL_Surface * initGLWindow(int width, int height, char * title, int fullscreen)
{
	SDL_Surface* pScreen = NULL;
	int nValue = 1;


	// SDL initialisation 
	if( SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Echec SDL_Init : %s\n",SDL_GetError());
		return NULL;
	}

	// when quitting the program
	atexit( SDL_Quit );

	// need the double buffer mode
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// video mode from SDL 
	pScreen = SDL_SetVideoMode(width, height, 32, fullscreen?SDL_OPENGL|SDL_FULLSCREEN:SDL_OPENGL);

	// window title
	SDL_WM_SetCaption(title,NULL);

	// is the window mode supported ?
	if( !pScreen )
	{
		printf("Echec de creation de la fenetre en %dx%d : %s\n",width,height,SDL_GetError() );
		return NULL;
	}

	// Check double buffer mode
	if( SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &nValue) < 0)
	{
		printf("Echec de recuperation du parametre SDL_GL_DOUBLEBUFFER : %s\n",SDL_GetError());
		return NULL;
	}

	// if not available stop the program
	if(nValue != 1)
	{
		printf("Erreur : SDL_GL_DOUBLEBUFFER inactif\n");
		return NULL;
	}

	initGL();
	
	return pScreen;
}



// INITGL
// To initialise OpenGL states
// RETURN : /
void initGL()
{
	// color to clear color & depth buffers
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClearDepth(1.0f);

	// use color on vertices
	glEnable(GL_COLOR_MATERIAL);

	// culling enable on faces : only draw the front faces
	glEnable(GL_CULL_FACE);

	// depth test is enable 
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// No lighting for the moment
	glDisable(GL_LIGHTING);

	// No texture used for the moment
	glDisable(GL_TEXTURE_2D);
	// if some are to be used, enable the correction regarding the perspective
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}


// DRAWCUBE
// to draw a unit cube but with the possibility to change its position and scale
// RETURN : /
// pos : position of the cube's center
// size : scale modification of the cube (uniform scale)
// rgb : color of the cube
void drawCube(vector3D pos,double size, color rgb)
{
	static int firstCall = 1;
	static GLuint idDisplayList = 0;
	
	// save the current ref
	glPushMatrix();

	// Move to draw 
	glTranslated(pos.x,pos.y,pos.z);
	// scale to draw the sphere
	glScaled(size,size,size);
	// modify the color
	glColor3f(	rgb.color[RED]/255.0f,rgb.color[GREEN]/255.0f,rgb.color[BLUE]/255.0f );


	if(firstCall)
	{
		
		idDisplayList = glGenLists(1);
		glNewList(idDisplayList,GL_COMPILE_AND_EXECUTE);
			// dessin d'un cube 
			glBegin(GL_QUADS);
				// DEVANT
				glNormal3d( 0.0,  0.0, 1.0);
				glVertex3d(-0.5,  0.5, 0.5);
				glVertex3d(-0.5, -0.5, 0.5);
				glVertex3d( 0.5, -0.5, 0.5);
				glVertex3d( 0.5,  0.5, 0.5);
			glEnd();
			glBegin(GL_QUADS);
				// DERRIERE
				glNormal3d(0.0,   0.0, -1.0);
				glVertex3d( 0.5,  0.5, -0.5);
				glVertex3d( 0.5, -0.5, -0.5);
				glVertex3d(-0.5, -0.5, -0.5);
				glVertex3d(-0.5,  0.5, -0.5);
			glEnd();
			glBegin(GL_QUADS);
				// DESSUS
				glNormal3d( 0.0,   1.0,  0.0);
				glVertex3d(-0.5,   0.5, -0.5);
				glVertex3d(-0.5,   0.5,  0.5);
				glVertex3d( 0.5,   0.5,  0.5);
				glVertex3d( 0.5,   0.5, -0.5);
			glEnd();
			glBegin(GL_QUADS);
				// DESSOUS
				glNormal3d( 0.0,  -1.0,  0.0);
				glVertex3d( 0.5,  -0.5, -0.5);
				glVertex3d( 0.5,  -0.5,  0.5);
				glVertex3d(-0.5,  -0.5,  0.5);
				glVertex3d(-0.5,  -0.5, -0.5);
			glEnd();
			glBegin(GL_QUADS);
				// GAUCHE
				glNormal3d(-1.0,   0.0,  0.0);
				glVertex3d(-0.5,   0.5, -0.5);
				glVertex3d(-0.5,  -0.5, -0.5);
				glVertex3d(-0.5,  -0.5,  0.5);
				glVertex3d(-0.5,   0.5,  0.5);
			glEnd();
			glBegin(GL_QUADS);
				// DROITE
				glNormal3d(1.0,   0.0,  0.0);
				glVertex3d( 0.5,   0.5,  0.5);
				glVertex3d( 0.5,  -0.5,  0.5);
				glVertex3d( 0.5,  -0.5, -0.5);
				glVertex3d( 0.5,   0.5, -0.5);
			glEnd();
		glEndList();

		firstCall = 0;
	}
	else glCallList(idDisplayList);

	// come back to the initial ref
	glPopMatrix();

}

// DRAWSPHERE
// to draw a sphere (diameter = 1 meter) but with the possibility to change its position and scale
// RETURN : /
// pos : position of the sphere's center
// size : scale modification of the sphere (uniform scale)
// rgb : color of the sphere
void drawSphere(vector3D pos,double size, color rgb)
{
	static int firstCall = 1;
	static GLuint idDisplayList = 0;
	

	// save the current ref
	glPushMatrix();

	// Move to draw 
	glTranslated(pos.x,pos.y,pos.z);
	// scale to draw the sphere
	glScaled(size,size,size);
	// modify the color
	glColor3f(	rgb.color[RED]/255.0f,rgb.color[GREEN]/255.0f,rgb.color[BLUE]/255.0f );


	if(firstCall)
	{
		int i,j;
		idDisplayList = glGenLists(1);
		glNewList(idDisplayList,GL_COMPILE_AND_EXECUTE);

			glPushMatrix();
			glScaled(0.5,0.5,0.5);
			for(i=0; i < SECTION_SPHERE; i++)
			{
				glBegin(GL_QUAD_STRIP);
				for(j=0; j < 2*SECTION_SPHERE+1; j++)
				{
					double x,y,z;
					x = cos(j*M_PI/(double)SECTION_SPHERE)*cos(-M_PI_2+i*M_PI/(double)SECTION_SPHERE);
					y = sin(-M_PI_2+i*M_PI/(double)SECTION_SPHERE);
					z = sin(j*M_PI/(double)SECTION_SPHERE)*cos(-M_PI_2+i*M_PI/(double)SECTION_SPHERE);
					glNormal3d(x,y,z);
					glVertex3d(x,y,z);
							
					x = cos(j*M_PI/(double)SECTION_SPHERE)*cos(-M_PI_2+(i+1)*M_PI/(double)SECTION_SPHERE);
					y = sin(-M_PI_2+(i+1)*M_PI/(double)SECTION_SPHERE);
					z = sin(j*M_PI/(double)SECTION_SPHERE)*cos(-M_PI_2+(i+1)*M_PI/(double)SECTION_SPHERE);
					glNormal3d(x,y,z);
					glVertex3d(x,y,z);
				}
				glEnd();
			}
			glPopMatrix();

		glEndList();

		firstCall = 0;
	}
	else glCallList(idDisplayList);

	// come back to the initial ref
	glPopMatrix();
}

// DRAWLINE
// to draw a line between 2 points
// RETURN  : /
// pos1 : position of the first point
// pos2 : position of the second point
// rgb : color of the line
//void drawLine(vector3D pos1, vector3D pos2, color rgb)
//{
//	glPushAttrib(GL_LIGHTING);
//	glDisable(GL_LIGHTING);
//
//	glBegin(GL_LINES);
//		glColor3f(rgb.r/255.0f, rgb.g/255.0f,rgb.b/255.0f);
//		glVertex3d(pos1.x,pos1.y,pos1.z);
//		glVertex3d(pos2.x,pos2.y,pos2.z);
//	glEnd();
//
//	glPopAttrib();
//}

// DRAWGRID
// draw a 10x10 grid
// RETURN : /
// size : scale of the grid
void drawGrid(double size)
{
	int i;
	
	glPushAttrib(GL_LIGHTING);
	glDisable(GL_LIGHTING);

	glPushMatrix();

	glScaled(0.05*size,0.05*size,0.05*size);
	
	glBegin(GL_LINES);
	glColor3f(0.05f,0.05f,0.05f);
	for(i=-10; i <= 10; i++)
	{
		glVertex3f( (GLfloat)i , 0.0 , -10.0 );
		glVertex3f( (GLfloat)i , 0.0 ,  10.0 );

		glVertex3f( -10.0 , 0.0 , (GLfloat)i );
		glVertex3f(  10.0 , 0.0 , (GLfloat)i );
	}
	glEnd();

	glPopMatrix();

	glPopAttrib();

}