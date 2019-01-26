#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "QuadTree.h"
#include "BMP.h"

QuadTree *CreateNode() {

	QuadTree* node = (QuadTree*)calloc(1, sizeof(QuadTree));
	for (int i = 0; i < NB_SQUARE; i++) {
		node->child[i] = NULL;
	}	
	return node;
}

pixel AveragePixel(pixel p_pixel1, pixel p_pixel2,  pixel p_pixel3, pixel p_pixel4) {
	pixel average;
	// Every member of average take the average value of each member of the 4 other pixels.
	for (int i = 0; i < NB_COLOR; i++) {
		average.value[i] = (p_pixel1.value[i] + p_pixel2.value[i] + p_pixel3.value[i] + p_pixel4.value[i]) / 4;
	}
	return average;
}

void PrintPixel(pixel p_pixel) {
	printf("[%d|%d|%d]", p_pixel.value[RED], p_pixel.value[GREEN], p_pixel.value[BLUE]);
}

void FreeQuad(QuadTree** p_node) {

	if (!p_node || !(*p_node)) {
		return;
	}
	// Free every child.
	for (int i = 0; i < NB_SQUARE; i++) {
		FreeQuad(&((*p_node)->child[i]));
	}
	free((*p_node));
	(*p_node) = NULL;	
}
// Returns 0 if every member of one pixel lower than a threshold, 1 else.
int ComparePixel(pixel p_pixel, byte p_threshold) {
	int lower = 0;
	for (int i = 0; i < NB_COLOR; i++) {
		if (p_pixel.value[i] > p_threshold) {
			return 1;
		}
	}
	return lower;
}
// Returns the abs value of the substraction of two pixels.
pixel SubstractPixel(pixel p_pixel1, pixel p_pixel2) {
	for (int i = 0; i < NB_COLOR; i++) {		
		p_pixel1.value[i] = (p_pixel1.value[i] >= p_pixel2.value[i]) ? p_pixel1.value[i] - p_pixel2.value[i]: p_pixel2.value[i] - p_pixel1.value[i];		
	}	
	return p_pixel1;
}

QuadTree *CreateQuad(pixel** p_pixel, int p_x, int p_y, int p_size, byte p_threshold) {

	QuadTree * node = CreateNode();
	int i = 0, nb_lower_pixel = 0;
	if (p_size != 1) {
		
		pixel average;
		for (i = 0; i < NB_SQUARE; i++) {
			node->child[i] = CreateNode();
		}
		node->child[UPPERLEFT] = CreateQuad(p_pixel, p_x, p_y, p_size / 2, p_threshold);
		node->child[BOTTOMLEFT] = CreateQuad(p_pixel, p_x, p_y + p_size / 2, p_size / 2, p_threshold);
		node->child[BOTTOMRIGHT] = CreateQuad(p_pixel, p_x + p_size / 2, p_y + p_size / 2, p_size / 2, p_threshold);
		node->child[UPPERRIGHT] = CreateQuad(p_pixel, p_x + p_size / 2, p_y, p_size / 2, p_threshold);
		average = AveragePixel(node->child[UPPERLEFT]->pixels, node->child[BOTTOMLEFT]->pixels, node->child[BOTTOMRIGHT]->pixels, node->child[UPPERRIGHT]->pixels);
		for (i = 0; i < NB_SQUARE; i++) {
			nb_lower_pixel += ComparePixel(SubstractPixel(average, node->child[i]->pixels), p_threshold);
			if (nb_lower_pixel) {
				break;
			}
		}		
		if (!nb_lower_pixel) {
			for (i = 0; i < NB_SQUARE; i++) {
				free((node)->child[i]);
				node->child[i] = NULL;
			}
		}		
		node->pixels = average;
	}
	else {				
		node->pixels = p_pixel[p_x][p_y];		
	}
	return node;
}

void SaveQuad(char* p_path, QuadTree* p_node){
	FILE* file = NULL;

	// Opening p_path. Binary Writing mode.
	file = fopen(p_path, "wb");

	if (!file)	{
		printf("[ERROR] Couldn't open \"%s\".\n", p_path);
		return;
	}
	// Going down the Quad.
	RouteQuad(p_node, file);
	fclose(file);	
}

void RouteQuad(QuadTree* p_node, FILE* p_file){
	if (!p_node || !p_file) {
		return;
	}
	// Writing the node value.
	fwrite(&(p_node->pixels), sizeof(pixel), 1, p_file);

	// Does the node have children ?
	byte child = 1;
	if (!(p_node->child[UPPERLEFT])) {
		child = 0;
	}
	fwrite(&child, sizeof(byte), 1, p_file);
	
	for (int i = 0; i < NB_SQUARE; i++) {
		RouteQuad(p_node->child[i], p_file);
	}	
}

QuadTree* LoadQuad(char* p_path){
	FILE* file = NULL;
	file = fopen(p_path, "rb");

	if (!file)	{
		printf("[ERROR] Couldn't open \"%s\".\n", p_path);
		return NULL;
	}	
	QuadTree* node = LoadingQuad(file);

	fclose(file);
	return node;
}

QuadTree* LoadingQuad(FILE* p_file){
	if (!p_file) {
		printf("[ERROR] file in LoadingQuad\n");
		return NULL;
	}
	int i;
	byte number;	
	QuadTree* node = CreateNode();

	// Reading bytes.
	fread(&(node->pixels), sizeof(pixel), 1, p_file);	
	fread(&number, sizeof(byte), 1, p_file);
	
	// If there is a 1, node does have children. We give them to it.
	if (number){		
		for (i = 0; i < NB_SQUARE; i++) {
			node->child[i] = LoadingQuad(p_file);
		}	
	}
	else{
		for (i = 0; i < NB_SQUARE; i++) {
			node->child[i] = NULL;
		}		
	}
	return node;
}

int Pow(int p_i, int p_pow){
	if (!p_pow) {
		return 1;
	}
	return p_i * Pow(p_i, p_pow - 1);
}

void CreatePicture(char* p_path, QuadTree* p_node, dword p_level){	
	
	picture* bmp = (picture*)calloc(1, sizeof(picture));	
	bmp->datas = (bmpInfoHeader*)calloc(1, sizeof(bmpInfoHeader));
	dword resolution = Pow(4, HeightQuad(p_node));
	// Height = width and height * width = resolution.
	bmp->datas->height = (dword)sqrt(resolution); 	
	bmp->datas->width = bmp->datas->height; 
	// 24 bits per pixel.
	bmp->datas->bitsperpixel = 24; 
	// Size of picture in bits.
	bmp->datas->sizeimage = resolution * bmp->datas->bitsperpixel; 
	bmp->datas->size = bmp->datas->width * bmp->datas->height;	
	bmp->datas->compression = 0;
	bmp->datas->type[0] = 'B';
	bmp->datas->type[1] = 'M';
	bmp->datas->headersize = 40;
	bmp->datas->offset = 54;
	bmp->datas->planes = 1;
	bmp->datas->xpixelspermeter = 2834;
	bmp->datas->ypixelspermeter = 2834;
	bmp->datas->colorused = 0;
	bmp->datas->colorsimportant = 0;

	// Creating the matrix of pixels.	
	bmp->matrix = (pixel**)calloc(bmp->datas->height, sizeof(pixel*));
	for (dword i = 0; i < bmp->datas->height; i++)	{
		bmp->matrix[i] = (pixel*)calloc(bmp->datas->width, sizeof(pixel));
	}
	// Filling the matrix.
	CreatingPicture(p_node, bmp->matrix, 0, bmp->datas->width, bmp->datas->height, 0, 0, p_level);
	WritePicture(bmp, p_path);
	FreeBMP(bmp);
}

void CreatingPicture(QuadTree* p_node, pixel** p_pixel, dword p_height, dword p_x_local, dword p_y_local, dword p_x, dword p_y, dword p_level){
	if (!p_node || !p_pixel) {
		return;
	}
	if (!(p_node->child[UPPERLEFT]) || p_level == p_height)	{
		dword i = 0, j = 0;
		for (i = p_x; i < p_x_local; i++){
			for (j = p_y; j < p_y_local; j++){
				p_pixel[i][j] = p_node->pixels;
			}
		}
		return;
	}
	CreatingPicture(p_node->child[UPPERLEFT], p_pixel, p_height + 1, p_x + ((p_x_local - p_x) / 2), p_y + ((p_y_local - p_y) / 2), p_x, p_y, p_level);
	CreatingPicture(p_node->child[BOTTOMLEFT], p_pixel, p_height + 1, p_x + (p_x_local - p_x) / 2, p_y_local, p_x, p_y + (p_y_local - p_y) / 2, p_level);
	CreatingPicture(p_node->child[BOTTOMRIGHT], p_pixel, p_height + 1, p_x_local, p_y_local, p_x + (p_x_local - p_x) / 2, p_y + ((p_y_local - p_y) / 2), p_level);
	CreatingPicture(p_node->child[UPPERRIGHT], p_pixel, p_height + 1, p_x_local, p_y + (p_y_local - p_y) / 2, p_x + (p_x_local - p_x) / 2, p_y, p_level);
}

int Sup(int x, int y){
	return (x >= y) ? x : y;
}

int HeightQuad(QuadTree* p_node){
	if (!p_node) {
		return -1;
	}
	int height = 0;
	int h_1 = HeightQuad(p_node->child[UPPERLEFT]);
	int h_2 = HeightQuad(p_node->child[BOTTOMLEFT]);
	int h_3 = HeightQuad(p_node->child[BOTTOMRIGHT]);
	int h_4 = HeightQuad(p_node->child[UPPERRIGHT]);
	int max = Sup(Sup(h_1, h_2), Sup(h_3, h_4));

	if (max == h_1) {
		height = h_1 + 1;
	}
	else {
		if (max == h_2) {
			height = h_2 + 1;
		}
		else {
			if (max == h_3) {
				height = h_3 + 1;
			}
			else {
				if (max == h_4) {
					height = h_4 + 1;
				}
			}
		}
	}
	return height;
}