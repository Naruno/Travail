#include "obj.h"

#include "utilSDL.h"
#include "../Librairies/FreeImage/FreeImage.h"

#pragma warning(disable : 4477)

// RESETOBJECTDATA
// to reset all the states of the object
// No deallocation is done in this function
// RETURN :  / 
// pObj : pointer on the object to be reseted
int resetObj(object * pObj)
{
	// error while calling the function
	if(!pObj) return 0;

	// reset the number of data
	pObj->nbVertex		=	0;
	pObj->nbNormal		=	0;
	pObj->nbUV			=	0;
	pObj->nbTriangle	=	0;
	//reset the arrays
	pObj->tabVertex		=	NULL;
	pObj->tabNormal		=	NULL;
	pObj->tabUV			=	NULL;
	pObj->tabTriangle	=	NULL;
	// reset the properties
	pObj->hasNormal		= 0;
	pObj->hasUV			= 0;
	// reset the OpenGL ID attached to the object
	pObj->displayListID = 0;
	pObj->texID			= 0;
	// Set the bounding box to nothing (centered in the world)
	SETVECTOR3D(pObj->boundingBox.minValues,0.0,0.0,0.0);
	SETVECTOR3D(pObj->boundingBox.maxValues,0.0,0.0,0.0);

	return 1;
}


// LOADOBJFROMFILE
// to load an object from an OBJ file
// The OBJ format is the only one supported
// Only one texture is supported per object and its name must be the same as the OBJ file (JPG/PNG and BMP supported)
// RETURN :  1 if everything is ok, 0 else
// pathFile : full path (absolute or relative) to the OBJ file
// pObj : pointer on the object to be loaded
int loadObjFromFile( const char *pathFile, object * pObj)
{
	// Variables
    FILE *fp = NULL;				// file pointer
   	char pathDir[BUF_SIZE] = {0};	// Directory path
	char fileName[BUF_SIZE] = {0};	// file name
	char buf[BUF_SIZE];				// buffer where data read in file are stored to be processed
    vector3D val;					// for reading without processing in file				
	double temp;					// for reading without processing in file
    int match;						// to count the number of data read in "buf"
	int iVertex,iUV,iNormal,iTriangle;	// current index for vertex/UV/Normal/triangle while reading in file

	// Error while calling the function
	if(!pathFile || !pObj) return 0;

	// init the object (BE CAREFUL : DEALLOCATION IS NOT DONE THERE, IT SHOULD BE DONE BEFORE CALLING loadObjFromFile)
	resetObj(pObj);

	// Open file
    fopen_s( &fp, pathFile, "rt");
	// if failed, stop the loading
    if (!fp)	return 0;

	// GET THE DIRECTOY & THE FILENAME IN ORDER TO BE ABLE TO GET THE TEXTURE
	{
		// Search for the last slash or backslash
		// search for the last point
		int i = 0;
		char * pFinder = (char*)pathFile;
		int indexSlash = -1;
		int indexPoint = -1;

		while(*pFinder!='\0')
		{
			if(*pFinder=='\\' || *pFinder=='/') indexSlash=i;
			if(*pFinder=='.' ) indexPoint=i;
						
			pFinder++;
			i++;
		}

		if(indexPoint<0) indexPoint = i;
					
		if(indexSlash>=BUF_SIZE)			
		{
				printf("Error : path two long [>%d]\n",BUF_SIZE);
				return 0;
		}
		if(indexPoint-indexSlash>=BUF_SIZE)	
		{
			printf("Error : filename two long [>%d]\n",BUF_SIZE);
			return 0;
		}
		// get the directory
		strncpy_s(pathDir,BUF_SIZE,pathFile,indexSlash+1);
		// get the filename (without extension).
		strncpy_s(fileName,BUF_SIZE,pathFile+indexSlash+1,indexPoint-indexSlash-1);

		// check the extension
		if(_stricmp("OBJ",pathFile+indexPoint+1))
		{
			printf("Error : extension is not managed by this loader.\nYou can only load OBJ file\n");
			return 0;
		}
	}


	// FIRST PASS : read the file to count the number of vertices/UVs/Normals/faces ...
    while ( fscanf_s( fp, "%s", buf, BUF_SIZE) != EOF ) {

        switch (buf[0]) {
            case '#':
                //comment line, eat the remainder
                fgets( buf, BUF_SIZE, fp);
                break;

            case 'v':
                switch (buf[1]) {
                
                    case '\0':
                        // check the vertex has 3 components and count the number of vertex
 						if(pObj->nbVertex==MAXINT)
						{
							printf("Error : two many vertices [>%d]\n",MAXINT);
							resetObj(pObj);
							return 0;
						}
                        match = fscanf_s( fp, "%lf %lf %lf %lf", &val.data[0], &val.data[1], &val.data[2], &temp);
                        if(match!=3) 
						{
							resetObj(pObj);
							return 0;
						}
						pObj->nbVertex++;
                        break;

                    case 'n':
                        // get the normal component & increment the number of normals
						if(pObj->nbNormal==MAXINT)
						{
							printf("Error : two many normals [>%d]\n",MAXINT);
							resetObj(pObj);
							return 0;
						}
                         match = fscanf_s( fp, "%lf %lf %lf", &val.data[0], &val.data[1], &val.data[2]);
						if(match!=3)
						{
							resetObj(pObj);
							return 0;
						}
						pObj->nbNormal++;
                       
                        break;

                    case 't':
                        // get the texture coordinates & increment the number of texcoord
						if(pObj->nbUV==MAXINT)
						{
							printf_s("Error : two many UVs [>%d]\n",MAXINT);
							resetObj(pObj);
							return 0;
						}
                        match = fscanf_s( fp, "%lf %lf %lf %lf", &val.data[0], &val.data[1], &val.data[2], &temp);
                        if(match!=3)
						{
							resetObj(pObj);
							return 0;
						}
						pObj->nbUV++;
						break;
                }
                break;

            case 'f':
                // get the face (triangle)

                if(pObj->nbTriangle==MAXINT) 
				{
					printf("Error : too many triangles [>%d]\n",MAXINT);
					resetObj(pObj);
					return 0;
				}
				
				fscanf_s( fp, "%s", buf, BUF_SIZE);
				{
					int nbVertexPerFace = 1;

					// get the face indices of vertex/texcoord/UV (texcoord and UV are optional)
					if ( sscanf_s( buf, "%d//%d", &val.data[0], &val.data[2]) == 2) {
						while ( fscanf_s( fp, "%d//%d", &val.data[0], &val.data[2]) == 2) nbVertexPerFace++;
						pObj->hasNormal	= 1;
					}
					else if ( sscanf_s( buf, "%d/%d/%d", &val.data[0], &val.data[1], &val.data[2]) == 3) {
						while ( fscanf_s( fp, "%d/%d/%d", &val.data[0], &val.data[1], &val.data[2]) == 3) nbVertexPerFace++;
						pObj->hasUV		= 1;
						pObj->hasNormal	= 1;
					}
					else if ( sscanf_s( buf, "%d/%d",  &val.data[0], &val.data[1]) == 2) {
						while ( fscanf_s( fp, "%d/%d", &val.data[0], &val.data[1]) == 2) nbVertexPerFace++;
						pObj->hasUV		= 1;
					}
					else if ( sscanf_s( buf, "%d", &val.data[0]) == 1) {
						while ( fscanf_s( fp, "%d", &val.data[0]) == 1) nbVertexPerFace++;
						pObj->hasUV		= 1;
					}

					if(nbVertexPerFace != 3)
					{
						resetObj(pObj);
						return 0;
					}

					pObj->nbTriangle++;
				}

                break;

            case 's':
            case 'g':
            case 'u':
                //all presently ignored
            default:
				// read line with other tokens to proceed the next lines of the file
                fgets( buf, BUF_SIZE, fp);
        };
    }
	
	// Allocate the arrays to store the vertex/normal/texcoord/triangles
	
	// VERTEX ARRAY
	pObj->tabVertex = (vector3D*)calloc(pObj->nbVertex,sizeof(vector3D));
	
	// TEXCOORD ARRAY
	if(pObj->hasUV)	pObj->tabUV = (vector3D*)calloc(pObj->nbUV,sizeof(vector3D));

	// NORMAL ARRAY
	if(pObj->hasNormal)	pObj->tabNormal = (vector3D*)calloc(pObj->nbNormal,sizeof(vector3D));

	// TRIANGLE ARRAY
	pObj->tabTriangle = (triangle*)calloc(pObj->nbTriangle,sizeof(triangle));
	if(!pObj->tabVertex || (pObj->hasUV && !pObj->tabUV) || (pObj->hasNormal && !pObj->tabNormal) || !pObj->tabTriangle)
	{
		freeObj(pObj);
		return 0;
	}

	// return to the beginning of the file
	fseek( fp, 0 , SEEK_SET );

	// SECOND PASS : to store the data in the dynamically allocated arrays

	// index of vertex/normal/texcoord/triangle to feed the array from the index 0 to the last index
	iVertex = iNormal = iUV = iTriangle = 0;
    while ( fscanf_s( fp, "%s", buf, BUF_SIZE) > 0 /*!= EOF*/ ) {

        switch (buf[0]) {
            case '#':
                //comment line, eat the remainder
                fgets( buf, BUF_SIZE, fp);
                break;

            case 'v':
                switch (buf[1]) {
                
                    case '\0':
                        //vertex
						fscanf_s( fp, "%lf %lf %lf", &pObj->tabVertex[iVertex].x, &pObj->tabVertex[iVertex].y, &pObj->tabVertex[iVertex].z);
						UPDATEBBOX(pObj->boundingBox,pObj->tabVertex[iVertex]);
						iVertex++;
                        break;

                    case 'n':
                        //normal
						fscanf_s( fp, "%lf %lf %lf", &pObj->tabNormal[iNormal].x, &pObj->tabNormal[iNormal].y, &pObj->tabNormal[iNormal].z);
						iNormal++;
                        break;

                    case 't':
                        //texcoord
                        fscanf_s( fp, "%lf %lf %lf", &pObj->tabUV[iUV].x, &pObj->tabUV[iUV].y, &pObj->tabUV[iUV].z);
                        iUV++;
                        break;
                }
                break;

            case 'f':
                //face (triangle)
              
                // get data from the triangle vertices
				{
					int i;
					//reset triangle indices
					int idx[3][3] = {0};

					fgets( buf, BUF_SIZE, fp);

					if(pObj->hasUV && pObj->hasNormal)
					{
						sscanf_s( buf, " %d/%d/%d %d/%d/%d %d/%d/%d", &idx[0][0], &idx[0][1], &idx[0][2], &idx[1][0], &idx[1][1], &idx[1][2], &idx[2][0], &idx[2][1], &idx[2][2]);
					}
					else if(pObj->hasUV)
					{
						 sscanf_s( buf, " %d/%d %d/%d %d/%d", &idx[0][0], &idx[0][1], &idx[1][0], &idx[1][1], &idx[2][0], &idx[2][1]);
					}
					else if(pObj->hasNormal)
					{
						 sscanf_s( buf, " %d//%d %d//%d %d//%d", &idx[0][0], &idx[0][2], &idx[1][0], &idx[1][2], &idx[2][0], &idx[2][2]);
					}
					else
					{
						 sscanf_s( buf, " %d %d %d", &idx[0][0],&idx[1][0], &idx[2][0]);
					}

					//remap them to the right spot
					// VERTEX
					idx[0][0] = (idx[0][0] > 0) ? (idx[0][0] - 1) : (pObj->nbVertex - idx[0][0]);
					idx[0][1] = (idx[0][1] > 0) ? (idx[0][1] - 1) : (pObj->nbUV		- idx[0][1]);
					idx[0][2] = (idx[0][2] > 0) ? (idx[0][2] - 1) : (pObj->nbNormal - idx[0][2]);
					//UV
					idx[1][0] = (idx[1][0] > 0) ? (idx[1][0] - 1) : (pObj->nbVertex - idx[1][0]);
					idx[1][1] = (idx[1][1] > 0) ? (idx[1][1] - 1) : (pObj->nbUV		- idx[1][1]);
					idx[1][2] = (idx[1][2] > 0) ? (idx[1][2] - 1) : (pObj->nbNormal - idx[1][2]);
					//NORMAL
					idx[2][0] = (idx[2][0] > 0) ? (idx[2][0] - 1) : (pObj->nbVertex	- idx[2][0]);
					idx[2][1] = (idx[2][1] > 0) ? (idx[2][1] - 1) : (pObj->nbUV		- idx[2][1]);
					idx[2][2] = (idx[2][2] > 0) ? (idx[2][2] - 1) : (pObj->nbNormal	- idx[2][2]);

					// fill the indices
					for ( i = 0; i < 3; i++) {
						pObj->tabTriangle[iTriangle].indexVertex[i]	= idx[i][0];
						pObj->tabTriangle[iTriangle].indexUV[i]		= idx[i][1];
						pObj->tabTriangle[iTriangle].indexNormal[i]	= idx[i][2];
					}

					// construct the normal of the face (not equal to the mean of the 3 normals)
					{
						vector3D norm,v1,v2;
						SUB(v1, pObj->tabVertex[ pObj->tabTriangle[iTriangle].indexVertex[1] ], pObj->tabVertex[ pObj->tabTriangle[iTriangle].indexVertex[0] ] );
						SUB(v2, pObj->tabVertex[ pObj->tabTriangle[iTriangle].indexVertex[2] ], pObj->tabVertex[ pObj->tabTriangle[iTriangle].indexVertex[0] ] );
						CROSS(norm,v2,v1);
						// if the triangle is not a line calculate the normal regarding its edges
						if( NORM(norm) > EPSILON)
						{
							NORMALIZE(pObj->tabTriangle[iTriangle].normal,norm);
						}
						// else do the mean of the 3 normals applied on its 3 vertices
						else
						{
							ADD(norm, pObj->tabNormal[ pObj->tabTriangle[iTriangle].indexNormal[0] ] ,pObj->tabNormal[ pObj->tabTriangle[iTriangle].indexNormal[1] ]);
							ADD(norm, norm, pObj->tabNormal[ pObj->tabTriangle[iTriangle].indexNormal[2] ] );
							NORMALIZE(pObj->tabTriangle[iTriangle].normal,norm);
						}
					}

					iTriangle++;
				}
                
                break;

            case 'g':
			case 's':
            case 'u':
            default:
				// go to next line to proceed
                fgets( buf, BUF_SIZE, fp);
        };
    }
    fclose(fp);

	// TEXTURE
	{
		// we will use the filename to find a texture (JPG/PNG/BMP)
		char extensions[3][4] = { "JPG","PNG","BMP" };
		int i;

		for(i=0; i<3; i++)
		{
			// Convert to BMP file path
			sprintf_s(buf,BUF_SIZE,"%s%s.%s",pathDir,fileName,extensions[i]);

			// Load the texture in video memory
			{
				// Get the image file type from FreeImage.
				FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(buf,0);

				// Actually load the image file.
				FIBITMAP *dib = FreeImage_Load(fifmt, buf, 0);

				if( !dib ) continue;

				// Now, there is no guarantee that the image file
				// loaded will be GL_RGB, so we force FreeImage to
				// convert the image to GL_RGB.
				dib = FreeImage_ConvertTo24Bits(dib);

				if( dib )
				{
					BYTE byteTemp;
					unsigned int pix;
					unsigned int width = FreeImage_GetWidth(dib);
					unsigned int height = FreeImage_GetHeight(dib);
					// get a pointer to FreeImage's data.
					unsigned char *pixels = (BYTE*)FreeImage_GetBits(dib);

					if(!pixels)
					{
						FreeImage_Unload(dib);
						pObj->texID = 0;
						continue;
					}

					// Invert B & R value
					for( pix=0; pix< width*height; pix++)
					{	
						byteTemp			= pixels[ pix*3 ];
						pixels[pix*3 ]		= pixels[pix*3+2];
						pixels[ pix*3+2 ]	= byteTemp;
					}

					// generate a texture on the video board
					glGenTextures( 1, &pObj->texID );
					// fill the texture with the pixels loaded by FreeImage
					if(pObj->texID)
					{
						glBindTexture( GL_TEXTURE_2D, pObj->texID );
						glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR );
						glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
						glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels );
					}

					// Unload the image.
					// and free the bit data.
					FreeImage_Unload(dib);
				}
			}
			if(pObj->texID) break;
		}

	}

	// DISPLAY LIST 
	// Create the display list calling the drawing function
	pObj->displayListID = glGenLists(1);
	if(pObj->displayListID>0)
	{
			
		glNewList(pObj->displayListID,GL_COMPILE);
			drawObjMesh(pObj);
		glEndList();
	}

    return 1;
}

// FREEOBJ
// to free all the data allocated for the object loaded
// it calls the resetObjectData function and deallocate everything
// RETURN :  1 is everything is OK, 0 else 
// pObj : pointer on the object to free
int freeObj(object * pObj)
{
	// delete everything which is need to
	if(pObj->displayListID)					glDeleteLists(pObj->displayListID,1);
	if(pObj->texID)							glDeleteTextures(1,&pObj->texID);
	if(pObj->tabVertex)						free(pObj->tabVertex);
	if(pObj->hasUV && pObj->tabUV)			free(pObj->tabUV);
	if(pObj->hasNormal && pObj->tabNormal)	free(pObj->tabNormal);
	if(pObj->tabTriangle)					free(pObj->tabTriangle);
	// reset the object states
	resetObj(pObj);
	return 1;
}

// DRAWOBJMESH
// to draw the mesh in "vertex-at-time" mode
// No texture applied
// RETURN : 1  1 is everything is OK, 0 else 
// pObj : pointer on the object to draw
int drawObjMesh(object * pObj)
{
	// error while calling the function
	if(!pObj) 
		return 0;

	glBegin(GL_TRIANGLES);
	{
		int i,j;

		//WHITE
		glColor3d(1.0,1.0,1.0);
	
		// DRAW ALL THE TRIANGLES
		for(i = 0; i < pObj->nbTriangle; i++)
		{
			//TRIANGLE number i
			for(j=0; j < 3; j++)
			{
				// NORMAL
				if(pObj->hasNormal) glNormal3d(		pObj->tabNormal[ pObj->tabTriangle[i].indexNormal[j] ].x,
													pObj->tabNormal[ pObj->tabTriangle[i].indexNormal[j] ].y,
													pObj->tabNormal[ pObj->tabTriangle[i].indexNormal[j] ].z
												);
				// UV
				if(pObj->hasUV)		glTexCoord2d(	pObj->tabUV[ pObj->tabTriangle[i].indexUV[j] ].x,
													pObj->tabUV[ pObj->tabTriangle[i].indexUV[j] ].y
												);
				// VERTEX
									glVertex3d(		pObj->tabVertex[ pObj->tabTriangle[i].indexVertex[j] ].x,
													pObj->tabVertex[ pObj->tabTriangle[i].indexVertex[j] ].y,
													pObj->tabVertex[ pObj->tabTriangle[i].indexVertex[j] ].z
												);
			}
		}
	}
	glEnd();

	return 1;
}

// DRAWOBJ
// if display list is enabled draw the object calling the display list
// if not call the drawObjMesh function
// texture is applied 
// RETURN : 1  1 is everything is OK, 0 else 
// pObj : pointer on the object to draw
int drawObj(object * pObj)
{
	int ret = 0;
	// error while calling the function
	if(!pObj) 
		return ret;

	// bind the texture if needed
	if(pObj->texID)
	{
		glPushAttrib(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,pObj->texID);
	}

	// call the display list if it exists
	if(pObj->displayListID)	
	{
		glCallList(pObj->displayListID);
		ret = 1;
	}
	// draw in "vertex-at-time" mode if no display list available
	else
	{
		ret = drawObjMesh(pObj);
	}
		
	// bind no texture & restore the previous OpenGL state for textures
	if(pObj->texID)
	{
		glBindTexture(GL_TEXTURE_2D,0);
		glPopAttrib();
	}


	return ret;

}


// DRAWOBJPOSSIZE
// Same as drawObj but we can modify position & size of the object thanks to pos/size inpput parameters
// RETURN : 1  1 is everything is OK, 0 else 
// pObj : pointer on the object to draw
int drawObjPosSize(object * pObj, vector3D pos, vector3D size)
{
	// returned value
	int ret=0;
			
	// error while calling the function
	if(!pObj)
		return ret;

	// Get the previous state of OpenLG for ligthing
	glPushAttrib(GL_LIGHTING|GL_LIGHT0);
	// Swicth on the lighting & swicth on light0
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// store the current modelview matrix
	glPushMatrix();

	// Move & scale to draw the object
	glTranslated(pos.x,pos.y,pos.z);
	glScaled(size.x,size.y,size.z);

	// Draw the object
	ret = drawObj(pObj);

	// restore the previous modelview matrix
	glPopMatrix();
	// restore the OpenGL states for lighting
	glPopAttrib();

	return ret;
	
}
