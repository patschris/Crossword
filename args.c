#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"

/* 
 * Handles the arguments and returns the proper values to the pointers dict, check, draw
 */
void handleArguments (int argc, char **argv, char **dict, int *check, int *draw) {
	if (argc < 2) {
		printf("You need at least to give the crossword\n");
		exit(-1);
	}
	*dict = pickDictionary(argc, argv);
	if (argc > 2) {
		*check = checkArgument(argc, argv);
		*draw = drawArgument(argc, argv);
	}
	else {
		*check = 0;
		*draw = 0;
	}
}

/*
 * Returns the name of the file that contains the dictionary
 * If -dict argument was given, then the next argument is the dictionary's name. Otherwise, we use the default dictionary "Words.txt"
 */
char *pickDictionary(int argc, char **argv) {
	char *dict;
	int pos = -1;
	for (int i=2; i < argc; i++) {
		if (!strcmp(argv[i],"-dict")) {
			pos = i+1;
			break;
		} 
	}
	if (pos > 0) {
		if ((dict = (char *) malloc ((strlen(argv[pos])+1)*sizeof(char))) == NULL) {
			perror("dict malloc failed");
			exit(-1);
		}
		memset(dict, '\0', (strlen(argv[pos]) + 1)*sizeof(char));
		strcpy(dict, argv[pos]);
	}
	else {
		if ((dict = (char *) malloc ((strlen("Words.txt")+1)*sizeof(char))) == NULL) {
			perror("dict malloc failed");
			exit(-1);
		}
		memset(dict, '\0', (strlen("Words.txt")+1)*sizeof(char));
		strcpy (dict, "Words.txt");
	}
	return dict;
}

/*
 * Checks if the argument -check was given and returns 1, otherwise 0
 */
int checkArgument (int argc, char **argv) {
	for (int i=2; i < argc; i++)
		if (!strcmp(argv[i],"-check")) return 1;
	return 0;
}

/*
 * Checks if the argument -draw was given and returns 1, otherwise 0
 */
int drawArgument (int argc, char **argv) {
	for (int i=2; i < argc; i++)
		if (!strcmp(argv[i],"-draw")) return 1;
	return 0;
}