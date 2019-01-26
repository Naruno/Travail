#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "BMP.h"

picture *ReadPicture(char *p_pctPath){		
	if (!p_pctPath)	{
		printf("[ERROR] Argument NULL in ReadPicture\n");
		return NULL;
	}
	dword i;
	bmpInfoHeader *data = NULL;
	picture* pct = NULL;
	FILE *reading = NULL;
	pixel** pixel_v = NULL;

	data = (bmpInfoHeader*)calloc(1, sizeof(bmpInfoHeader));
	pct = (picture*)calloc(sizeof(picture), 1);

	if (!pct || !data) {
		printf("[ERROR] While allocation pct or data.\n");
	}
	// Openning the picture.
	printf("Reading \"%s\"\n", p_pctPath);
	reading = fopen(p_pctPath, "rb");
	if (!reading){
		printf("[ERROR] Couldn't open %s\n", p_pctPath);
		return 0;
	}	
	// Reading the header.
	fread(data, 54, 1, reading);	
	pct->datas = data;
	
	// Reading pixels.
	pixel_v = (pixel**)calloc(data->height, sizeof(pixel*));
	if (!pixel_v) {
		printf("[ERROR] While allocating pixel_v.\n");
		return NULL;
	}
	for (i = 0; i < data->height; i++) {
		pixel_v[i] = (pixel*)calloc(data->width, sizeof(pixel));
	}
	// Putting pixels in the height lines of the matrix.
	for (i = 0; i < data->height; i++)	{
		fread(pixel_v[i], 3, data->width, reading);		
	}		
	fclose(reading);
	pct->matrix = pixel_v;	

	free(*pixel_v);
	return pct;
}

int WritePicture(picture *p_pct, char *p_pctPath){
	
	if (!p_pct || !p_pctPath){
		printf("Arguent NULL in WritePicture\n");
		return 0;
	}
	dword i;
	FILE *output = NULL;
	
	// Openning file, Writing header and pixels.
	output = fopen(p_pctPath, "wb");
	fwrite(p_pct->datas, 54, 1, output);
	for (i = 0; i < p_pct->datas->height; i++)	{
		fwrite(p_pct->matrix[i], 3, p_pct->datas->width, output);
	}
	fclose(output);
	return 1;
}

void PrintHeader(bmpInfoHeader* p_datas) {

	printf("[I] type : %s\n", p_datas->type);
	printf("[I] size : %d\n", p_datas->size);
	printf("[I] offset : %d\n", p_datas->offset);
	printf("[I] headersize : %d\n", p_datas->headersize);
	printf("[I] width : %d\n", p_datas->width);
	printf("[I] height : %d\n", p_datas->height);
	printf("[I] planes : %d\n", p_datas->planes);
	printf("[I] bitsperpixel : %d\n", p_datas->bitsperpixel);
	printf("[I] compression : %d\n", p_datas->compression);
	printf("[I] sizeimage : %d\n", p_datas->sizeimage);
	printf("[I] xpixelspermeter : %d\n", p_datas->xpixelspermeter);
	printf("[I] ypixelspermeter : %d\n", p_datas->ypixelspermeter);
	printf("[I] colorused : %d\n", p_datas->colorused);
	printf("[I] colorsimportant : %d\n", p_datas->colorsimportant);
	return;
}

void FreeBMP(picture* p_pct){
	if (!p_pct) {
		printf("[ERROR] p_pct NULL in FreeBMP.\n");
		return;
	}
	free(p_pct->matrix);
	free(p_pct);
	p_pct = NULL;	
}