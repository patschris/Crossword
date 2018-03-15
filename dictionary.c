#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"
#include "dictList.h"
#include "dictionary.h"

/*
 * Open the file that contains the dictionary and returns a file pointer
 */
FILE *openDictionary (char *dict) {
	FILE *fp;
	if ((fp = fopen(dict,"r")) == NULL) {
		perror("dictionary file fopen failed");
    	exit(-1);
	}
	return fp;
}

/*
 * Read line by line the dictionary file and insert the word in a list depending on its length
 */
void readDictionary (FILE *fp, DictList ***l) {
	char buf[MAXWORD];
	if ((*l = (DictList **) malloc((MAXWORD+1)*sizeof(DictList*)))== NULL) {
		perror("Dictionary malloc failed");
		exit(-1);
	}
	for (int i=0; i<MAXWORD+1; i++) (*l)[i] = createDictList();
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		buf[strlen(buf)-1] = '\0';
		insertDictNode((*l)[strlen(buf)], buf);
	}
}

/*
 * Destroy the structure that contains all the words of the dictionary
 */
void destroyDictionary (DictList **l) {
	for (int i=0; i<MAXWORD+1; i++) destroyDictList(l[i]);
	free(l);
}

/*
 * Print the dictionary by printing one list per word length
 */
void printDictionary(DictList **l) {
	printf("################################################\n");
	for (int i=0; i<MAXWORD+1; i++) {
		printf("List %d\n", i);
		printDictList(l[i]);
		printf("################################################\n");
	}
}