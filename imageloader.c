/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				wnw231423
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	FILE *fp = fopen(filename, "r");
	Image *res = (Image*) malloc(sizeof(Image));

	char str[20];
	int m, n, r, g, b;
	fscanf(fp, "%s", str);
	fscanf(fp, "%d%d", &m, &n);
	res->cols = m;
	res->rows = n;

	res->image = (Color**) malloc(n * sizeof(Color*));
	for (int i = 0; i < n; i++) {
		res->image[i] = (Color*) malloc(m * sizeof(Color*));
	}

	fscanf(fp, "%d", &r);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fscanf(fp, "%d%d%d", &r, &g, &b);
			Color node;
			node.R = r;
			node.G = g;
			node.B = b;
			res->image[i][j] = node;
		}
	}
	fclose(fp);
	return res;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	printf("P3\n");
	printf("%d %d\n", image->cols, image->rows);
	printf("255\n");
	for (int i = 0; i < image->rows; i++) {
		for (int j = 0; j < image->cols; j++) {
			if (j != 0) {
				printf("   ");
			}
			printf("%3d %3d %3d", image->image[i][j].R, image->image[i][j].G, image->image[i][j].B);
			if (j == image->rows - 1) {
				printf("\n");
			}
		}
	}
}

//Frees an image
void freeImage(Image *image)
{
	free(image);
}
