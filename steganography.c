/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				wnw231423
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col){
	Color *res = (Color*) malloc(sizeof(Color));
	uint8_t blue = image->image[row][col].B;
	if ((blue & 0b00000001) == 0b00000001) {
		res->B = 255;
		res->G = 255;
		res->R = 255;
	} else {
		res->G = 0;
		res->B = 0;
		res->R = 0;
	}
	return res;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	Image *res = (Image*) malloc(sizeof(Image));
	int rows = image->rows;
	int cols = image->cols;
	res->cols = cols;
	res->rows = rows;
	res->image = (Color**) malloc(sizeof(Color*) * rows);
	for (int i = 0; i < rows; i++) {
		res->image[i] = (Color*) malloc(sizeof(Color) * cols);
	}

	for (int i = 0; i < rows; i++) {
		//res->image[i] = (Color*) malloc(sizeof(Color) * cols);
		for (int j = 0; j < cols; j++) {
			Color *pixel = evaluateOnePixel(image, i, j);
			res->image[i][j] = *pixel;
			free(pixel);
		}
	}
	return res;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	if (argc != 2) {
		return -1;
	}
	char *filename = argv[1];
	Image *file = readData(filename);
	if (file == 0) {
		return -1;
	}
	Image *res = steganography(file);
	writeData(res);
	freeImage(file);
	freeImage(res);
	return 0;
}
