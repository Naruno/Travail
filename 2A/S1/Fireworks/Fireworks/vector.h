#ifndef _VECTOR3D_
#define _VECTOR3D_


// threshold under which data is estimated to be 0
#define EPSILON 0.000001

////////////////////////////// VECTOR 3D ////////////////////////////////////////////

// structure to store a 3D vector
// can be used as an array : .data[] 
// or adressing direclty the coordinates : .x/.y/.z
typedef union{
		struct { double x,y,z; };
		double data[3];
}vector3D;


// CROSSPRODUCT
// calculate the cross product bewteen 2 vectors. BE CAREFUL of the vectors'order
// v1 : first vector
// v2 : second vector
#define CROSS(dest,v1,v2) \
			dest.x = v1.y*v2.z-v1.z*v2.y; \
			dest.y = v1.z*v2.x-v1.x*v2.z; \
			dest.z = v1.x*v2.y - v1.y*v2.x;


// DOTPRODUCT
// to calulate the dot product bewteen 2 vectors
// v1 : fist vector
// v2 : second vector
#define DOT(v1,v2) (v1.x*v2.x+v1.y*v2.y+ v1.z*v2.z )

// ADDITION
// calculate the addition of 2 vectors
// v1 : fisrt vector
// v2: second vector
#define ADD(dest,v1,v2) \
			dest.x = v1.x + v2.x; \
			dest.y = v1.y + v2.y; \
			dest.z = v1.z + v2.z;

//SUBSTRACTION
// calculate the substraction bewteen 2 vectors.  BE CAREFUL of the vectors'order
// a first vector
// b : second vector
#define SUB(dest,v1,v2) \
			dest.x = v1.x - v2.x; \
			dest.y = v1.y - v2.y; \
			dest.z = v1.z - v2.z;

// MULTIPLICATION
// calculate the multiplication of a vector by a scalar
// v1 : vector
// v2 : scalar
#define MUL(dest,v,s) \
			dest.x = v.x*s; \
			dest.y = v.y*s; \
			dest.z = v.z*s;

#define DIV(dest,v,s) MUL(dest,v,1.0/(double)s)

// LENGTH
// to calculate the norm of the vector
// v : vector on which norm is calculted
#define NORM(v) sqrt( v.x*v.x+v.y*v.y+v.z*v.z ) 

// NORMALIZE
// to normalize a vector
// v : vector to normalize
// dest : normalized vector
#define NORMALIZE(dest,v) DIV(dest,v,NORM(v))

// DISTANCE
// calculate the distance between 2 vectors
// v1 : fisrt vector
// v2 : second vector
#define DISTANCE(v1,v2) sqrt( (v2.x-v1.x)*(v2.x-v1.x)+(v2.y-v1.y)*(v2.y-v1.y)+(v2.z-v1.z)*(v2.z-v1.z) )

#define EQUALS(v1,v2) (v1.x==v2.x && v1.y==v2.y && v1.z==v2.z)

#define REFLECT(dest,v,n) \
			{ \
				vector3D temp; \
				MUL(temp,n,-2.0*DOT(v,n)); \
				ADD(dest,temp,v); \
			}

// COPYVECTOR3D
// copy the current vector in another structure
// src : vector to copy
// dest : destination vector
#define COPYVECTOR3D(dest,src) \
			dest.x = src.x; \
			dest.y = src.y; \
			dest.z = src.z;


// SETVECTOR3D
// To initialize a 3D vector with its coordinates (x,y,z)
// xx,yy,zz : coordinates to set in the new vector
// dest : vector initialised
#define SETVECTOR3D(dest,xx,yy,zz) \
			dest.x = xx; \
			dest.y = yy; \
			dest.z = zz;

// INTEGRATION
// calculate the position(speed) integrating speed(acceleration) with time interval dt
// p : position (or speed)
// v : speed (or acceleration)
// dt : time interval
// dest : new position (new speed)
#define INTEGRATE(dest,p,v,dt) \
			dest.x = p.x + v.x*dt; \
			dest.y = p.y + v.y*dt; \
			dest.z = p.z + v.z*dt;

// MINIMUM 
// get the minimum per coordinate between 2 vectors
// v1, v2 : the 2 vectors to compare
// dest : vector filled with the minimum coordinates
#define MIN(dest,v1,v2) \
			dest.x = v1.x>v2.x?v2.x:v1.x; \
			dest.y = v1.y>v2.y?v2.y:v1.y; \
			dest.z = v1.z>v2.z?v2.z:v1.z;

// MAXIMUM 
// get the minimum per coordinate between 2 vectors
// v1, v2 : the 2 vectors to compare
// dest : vector filled with the minimum coordinates
#define MAX(dest,v1,v2) \
			dest.x = v1.x<v2.x?v2.x:v1.x; \
			dest.y = v1.y<v2.y?v2.y:v1.y; \
			dest.z = v1.z<v2.z?v2.z:v1.z;

// ISINBOUNDINGDOX
// check if the vector is in a bounding box, return 0 if not
// v : vector to check
// b : bounding box
#define ISINBBOX(b,v) ( v.x>=b.minValues.x && v.x <=b.maxValues.x && v.y>=b.minValues.y && v.y <=b.maxValues.y && v.z>=b.minValues.z && v.z <=b.maxValues.z)




// to define a bounding box 
typedef struct sBBox {
	vector3D minValues;
	vector3D maxValues;
} bBox;

// UPDATEBOUNDINGBOX
// update the bounding box regarding the vector given in parameter
// b : bounding box
// v : vector to include in the bounding box
#define UPDATEBBOX(b,v) \
	if( !ISINBBOX( b , v) ) {\
		MIN(b.minValues,b.minValues,v); \
		MAX(b.maxValues,b.maxValues,v); \
	}






////////////////////////////// COLOR ////////////////////////////////////////////

// color vector
typedef struct sColor {
	unsigned char color[3];
}color;


// COPYCOLOR
// copy the color in another color vector structure
// src  : color vector to copy
// dest : color copied
#define COPYRGB(dest,src) \
			dest.color[RED] = src.color[RED]; \
			dest.color[GREEN] = src.color[GREEN]; \
			dest.color[BLUE] = src.color[BLUE];

// SETCOLOR
// To initialize a color vector with its coordinates (r,g,b)
// rr,gg,bb : coordinates to set in the new color vector
// dest : color filled
#define SETRGB(dest, rr,gg,bb) \
			dest.color[RED] =rr; \
			dest.color[GREEN] = gg; \
			dest.color[BLUE] = bb;

// SAMECOLOR
// egality test between 2 colors, return 0 if not equals 
// rgb1 : fisrt color
// rgb2 : second color
#define SAMERGB(rgb1,rgb2) (rgb1.color[RED] == rgb2.color[RED] && rgb1.color[GREEN] == rgb2.color[GREEN] && rgb1.color[BLUE] == rgb2.color[BLUE])




#endif