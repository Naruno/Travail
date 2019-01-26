#ifndef _LOADER_OBJ_
#define _LOADER_OBJ_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// Max buffer size
#define BUF_SIZE	1024

// to define a triangle regarding the other arrays already stored (defined with index in the vertex/UV/normal arrays)
// added : normal of the triangle which is calculated from 2 segments of the triangle (cross product normalized)
typedef struct sTriangle {
	int indexVertex[3];			// vertices indices 
	int indexNormal[3];			// normals indices 
	int indexUV[3];				// texture coordinates indices
	vector3D normal;			// single normal for the triangle (only used for reflection calculation while intersection is found)
}triangle;


// BE CAREFUL : using int implies that the number of vertex/UV/Normal/triangle MUST be less than MAXINT
// the number of vertex/UV/normal/triangle is not checked while loading from the file so the object should be "little" enough to fit this structure unless the program will crash
typedef struct sObject {
	int nbVertex;				// number of vertices
	int nbUV;					// number of texture coordinates
	int nbNormal;				// number of normals
	int nbTriangle;				// number of triangles
	vector3D * tabVertex;		// array of vertices
	vector3D * tabNormal;		// array of normals
	vector3D * tabUV;			// array of texture coordinates
	triangle * tabTriangle;		// array of triangles
	unsigned char hasNormal;	// normal state
	unsigned char hasUV;		// texture coordinate state	
	unsigned int displayListID;	// display list ID for OpenGL display
	unsigned int texID;			// texture ID for OpenGL display
	bBox	boundingBox;		// bounding box for intersection calculation acceleration
}object;


// RESETOBJECTDATA
// to reset all the states of the object
// No deallocation is done in this function
// RETURN :  / 
// pObj : pointer on the object to be reseted
void resetObjectData(object * pObj);

// LOADOBJFROMFILE
// to load an object from an OBJ file
// The OBJ format is the only one supported
// Only one texture is supported per object and its name must be the same as the OBJ file (JPG/PNG and BMP supported)
// RETURN :  1 if everything is ok, 0 else
// pathFile : full path (absolute or relative) to the OBJ file
// pObj : pointer on the object to be loaded
int loadObjFromFile(const char * pathFile, object * pObj);

// FREEOBJ
// to free all the data allocated for the object loaded
// it calls the resetObjectData function and deallocate everything
// RETURN :  1 is everything is OK, 0 else 
// pObj : pointer on the object to free
int freeObj(object * pObj);

// DRAWOBJMESH
// to draw the mesh in "vertex-at-time" mode
// No texture applied
// RETURN : 1  1 is everything is OK, 0 else 
// pObj : pointer on the object to draw
int drawObjMesh(object * pObj);

// DRAWOBJ
// if display list is enabled draw the object calling the display list
// if not call the drawObjMesh function
// texture is applied 
// RETURN : 1  1 is everything is OK, 0 else 
// pObj : pointer on the object to draw
int drawObj(object * pObj);

// DRAWOBJPOSSIZE
// Same as drawObj but we can modify position & size of the object thanks to pos/size inpput parameters
// RETURN : 1  1 is everything is OK, 0 else 
// pObj : pointer on the object to draw
int drawObjPosSize(object * pObj, vector3D pos, vector3D size);

#endif