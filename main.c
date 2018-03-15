#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"
#include "slotList.h"
#include "args.h"
#include "dictList.h"
#include "crossword.h"
#include "dictionary.h"
#include "solve.h"

int main(int argc, char *argv[]) {
	
	FILE *fp;
	int check, draw;
	DictList **dictionary = NULL;
	char buf[ROWSIZE], *dictFile = NULL;

	/* Check the given arguments */
	handleArguments (argc, argv, &dictFile, &check, &draw);
	
	/* Open the file that contains crossword's grid */
	if ((fp = fopen(argv[1],"r")) == NULL) {
		perror("crossword file fopen failed");
    	return -1;
	}
	
	/* Read the first line that contains the size of the crossword */
	fgets(buf, sizeof(buf), fp);
	int size = atoi(buf);
	
	/* Allocate space for the crossword and initialize based on the file that contains crossword's grid */
	char *crossword = allocateCrossword(size);
	fillBlackCells (fp, crossword, size);
	fclose(fp);
	
	/* Open the crossword, read and save the words based on word's length */
	fp = openDictionary(dictFile);
	readDictionary(fp, &dictionary);
	fclose(fp);

	/* Find the slots that I have to fill vertically */
	SlotList * verticalSlots = createSlotList();
	/* Find the slots that I have to fill horizontally */
	SlotList * horizontalSlots = createSlotList();
	findHorizontalSlots (horizontalSlots, crossword, size, 1);
	findVerticalSlots (verticalSlots, crossword, size, 1);
	/* Merge and sort the two lists based on words length and direction */
	SlotList * slots = mergeLists(horizontalSlots, verticalSlots);
	/* Contains all the slots to fill first horizontally and then vertically */
	SlotList * checkSlots = createSlotList();
	findHorizontalSlots (checkSlots, crossword, size, 0);
	findVerticalSlots (checkSlots, crossword, size, 0);

	/* If argument check is given, I test if the given words can be placed into the crossword */
	if (check) {
		if (checkSolution (checkSlots, dictionary, crossword, size) && draw) 
			printCrossword(crossword, size);
	}
	else {
		if (solve(crossword,size, slots->first,dictionary)) {
			/* If argument draw is given, I draw the crossword, otherwise I only print the words that solve it */
			if (!draw) printSolution(crossword, size, checkSlots);
			else printCrossword(crossword, size);
		}
		else {
			printf("There is no valid solution\n");
		}
	}
	
	/* Deallocating all the memory used in the program */
	destroyDictionary(dictionary);
	destroyCrossword(crossword);
	destroySlotList(slots);
	destroySlotList(checkSlots);
	free(dictFile);

	return 0;
}