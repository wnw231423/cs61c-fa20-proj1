/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**              wnw231423
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"



//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	uint8_t red = image->image[row][col].R;
	uint8_t green = image->image[row][col].G;
	uint8_t blue = image->image[row][col].B;
	
	uint32_t current = (red << 16) | (green << 8) | blue;

	int row_neighbors[3];
	int col_neighbors[3];
	row_neighbors[0] = (row - 1 + image->rows) % image->rows;
	row_neighbors[1] = row;
	row_neighbors[2] = (row + 1) % image->rows;
	col_neighbors[0] = (col - 1 + image->cols) % image->cols;
	col_neighbors[1] = col;
	col_neighbors[2] = (col + 1) % image->cols;

	uint32_t res = 0;
	for (int i = 0; i < 24; i++) {
		int current_state = current >> i & 1;
		int neighbor_num = 0;
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				if (j == 1 && k == 1) {
					continue;
				}
				Color current_neighbor = image->image[row_neighbors[j]][col_neighbors[k]];
				uint32_t neighbor_color = (current_neighbor.R << 16) | (current_neighbor.G << 8) | current_neighbor.B;
				if ((neighbor_color >> i & 1) == 1) {
					neighbor_num += 1;
				}
			}
		}
		int next_state;
		if (current_state == 1) {
			next_state = rule >> (neighbor_num + 9) & 1;
		} else {
			next_state = rule >> neighbor_num & 1;
		}
		res = next_state << i | res;
	}
	
	uint8_t res_red = res >> 16;
	uint8_t res_green = res >> 8 & 255;
	uint8_t res_blue = res & 255;

	Color* res_color = (Color*) malloc(sizeof(Color));
	res_color->R = res_red;
	res_color->G = res_green;
	res_color->B = res_blue;
	return res_color;	
}


//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
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
			Color *pixel = evaluateOneCell(image, i, j, rule);
			res->image[i][j] = *pixel;
			free(pixel);
		}
	}
	return res;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	if (argc != 3) {
		printf("usage: ./gameOfLife filename rule\nfilename is an ASCII PPM file (type P3) with maximum value 255.\nrule is a hex number beginning with 0x; Life is 0x1808.\n");
		return -1;
	}
	char *filename = argv[1];
	uint32_t rule = (uint32_t) strtol(argv[2], NULL, 16);
	Image *file = readData(filename);
	if (file == 0) {
		return -1;
	}
	Image *res = life(file, rule);
	writeData(res);
	freeImage(file);
	freeImage(res);
	return 0;
}
