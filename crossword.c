#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"

/*
 * Allocate an array of chars to represent the crossword 
 */
char *allocateCrossword (int size) {
	char *arr;
	if ((arr = (char *)malloc((size*size)*sizeof(char))) == NULL) {
		perror("crossword malloc failed");
		exit(-1);
	}
	return arr;
}

/*
 * Fill with '#' the black cells based on the given crossword's grid. The other cells are empty
 */
void fillBlackCells (FILE *fp, char *arr, int size) {
	char buf[ROWSIZE], *tok[2];
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		tok[0] = strtok (buf," ");
		tok[1] =  strtok (NULL," ");
		arr[(atoi(tok[0])-1)*size+(atoi(tok[1])-1)] = '#';
	}
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			if (arr[i*size+j] != '#') {
				arr[i*size+j] = '\0';
			}
		}
	}

}

/*
 * Prints the crossword (-draw argument)
 */
void printCrossword (char *arr, int size) {
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			if (arr[i*size+j] != '\0') printf("%c ", arr[i*size+j]);
			else printf("  ");
		}
		printf("\n");
	}
}

/*
 * Deallocate crossword's memory
 */
void destroyCrossword(char *arr) {
	free(arr);
}