#ifndef QUADTREE_H
#define QUADTREE_H
#include "BMP.h"

enum children {
	UPPERLEFT,
	BOTTOMLEFT,
	BOTTOMRIGHT,
	UPPERRIGHT,
	NB_SQUARE
};

typedef struct QuadTree_s QuadTree;
struct QuadTree_s{	
	pixel pixels;
	QuadTree* child[4];
};

QuadTree *CreateNode();
void FreeQuad(QuadTree** p_node);
pixel AveragePixel(pixel p_pixel1, pixel p_pixel2, pixel p_pixel3, pixel p_pixel4);
pixel SubstractPixel(pixel p_pixel1, pixel p_pixel2);
void PrintPixel(pixel p_pixel);
int ComparePixel(pixel p_pixel, byte p_threshold);

void SaveQuad(char* p_path, QuadTree* p_node);
void RouteQuad(QuadTree* p_node, FILE* p_file);
int Pow(int i, int pow);

QuadTree *CreateQuad(pixel** p_pixel, int p_x, int p_y, int p_size, byte p_threshold);

QuadTree* LoadQuad(char* p_path);
QuadTree* LoadingQuad(FILE* p_file);
int Pow(int p_i, int p_pow);
void CreatePicture(char* p_path, QuadTree* p_node, dword p_level);
void CreatingPicture(QuadTree* p_node, pixel** p_pixel, dword p_height, dword p_x_local, dword p_y_local, dword p_x, dword p_y, dword p_level);
int Sup(int p_x, int p_y);
int HeightQuad(QuadTree* p_node);
#endif 