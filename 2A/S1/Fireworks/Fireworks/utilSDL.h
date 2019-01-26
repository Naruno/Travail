#ifndef _UTILSDL_
#define _UTILSDL_

#include <Windows.h>
#include <GL/GL.h>
#include "../Librairies/SDL-1.2.15/include/SDL.h"
#include "vector.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define SECTION_SPHERE	4

// INITGLWINDOW
// to create the OpenGL Window at width x height resolution with its title in fullscreen or not
// RETURN : the pointer on the SDL_Surface used to draw in the window
// width : width of the window
// height : height of the window
// title : title of the window
// fullscreen : "boolean" value to set the window in fullscreen (!=0) or not (0)
SDL_Surface * initGLWindow(int width, int height, char * title, int fullscreen);

// INITGL
// To initialise OpenGL states
// RETURN : /
void initGL(void);

// DRAWCUBE
// to draw a unit cube but with the possibility to change its position and scale
// RETURN : /
// pos : position of the cube's center
// size : scale modification of the cube (uniform scale)
// rgb : color of the cube
void drawCube(vector3D pos,double size, color rgb);

// DRAWSPHERE
// to draw a sphere (diameter = 1 meter) but with the possibility to change its position and scale
// RETURN : /
// pos : position of the sphere's center
// size : scale modification of the sphere (uniform scale)
// rgb : color of the sphere
void drawSphere(vector3D pos,double size, color rgb);

// DRAWLINE
// to draw a line between 2 points
// RETURN  : /
// pos1 : position of the first point
// pos2 : position of the second point
// rgb : color of the line
//void drawLine(vector3D pos1, vector3D pos2, color rgb);
#define DRAWLINE(pos1,pos2,rgb) \
			glPushAttrib(GL_LIGHTING); \
			glDisable(GL_LIGHTING); \
			glBegin(GL_LINES); \
				glColor3f(rgb.r/255.0f, rgb.g/255.0f,rgb.b/255.0f); \
				glVertex3d(pos1.x,pos1.y,pos1.z); \
				glVertex3d(pos2.x,pos2.y,pos2.z); \
			glEnd(); \
			glPopAttrib();

// DRAWGRID
// draw a 10x10 grid
// RETURN : /
// size : scale of the grid
void drawGrid(double size);

#endif