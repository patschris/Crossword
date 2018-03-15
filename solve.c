#include <stdio.h>
#include <string.h>
#include "declarations.h"
#include "dictList.h"
#include "slotList.h"
#include "crossword.h"
#include "solve.h"

/* 
 *Checks if crossword's position (x,y) is empty
 */ 
int isEmptyPos (char *cros, int size, int x, int y ) { 
	return (cros[x*size+y] == '\0'); 
}

/*
 * Finds the slots to fill in the horizontal direction 
 * Mode = 0 : insert slot in the list using insertion sort
 * Mode = 1 : insert slot at the end of the list
 */
void findHorizontalSlots (SlotList *l, char *crossword, int size, int mode) {
	for (int x = 0; x < size; x++) {
		for (int y = 0 ; y < size-1 ; y++) {
			if (isEmptyPos(crossword, size, x, y) && isEmptyPos(crossword, size, x, y+1)) {
				for (int sz = 2 ; y+sz < size && isEmptyPos(crossword, size, x, y+sz); sz++); // Find slot size
				if (mode) insertSlot(l, x, y, sz, HORIZONTAL);
				else insertAtEnd (l, x, y, sz, HORIZONTAL);
				y += sz; // Skip past this vertical slot
			}
		}
	}
}

/*
 * Finds the slots to fill in the vertical direction 
 * Mode = 0 : insert slot in the list using insertion sort
 * Mode = 1 : insert slot at the end of the list
 */
void findVerticalSlots (SlotList *l, char *crossword, int size, int mode) {
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size-1; x++) {
			if (isEmptyPos(crossword, size, x, y) && isEmptyPos(crossword, size, x+1, y)) {
				for (int sz = 2 ; x+sz < size && isEmptyPos(crossword, size, x+sz, y); sz++); 
				if (mode) insertSlot(l, x, y, sz, VERTICAL);
				else insertAtEnd (l, x, y, sz, VERTICAL);
				x += sz; // Skip past this horizontal slot
            }
		}
	}
}

/*
 * Checks if the given words solve the crossword
 * Prints proper error message if needed
 */
int checkSolution (SlotList *sl, DictList **dl, char *crossword, int size) {
	char str[MAXWORD];
	int counter = 0, limit = sl->size;
	Slot *slot = sl->first;
	while (scanf(" %s", str) == 1) {
		counter ++;
		if (counter > limit) {
			printf("More words than needed\n");
			return 0;
		}
		if (!searchWord (dl[(int)strlen(str)], str)) {
			printf("word \"%s\" not in dictionary\n", str);
			return 0;
		}
		if (!placeWord(slot, crossword, size, str)) {
			printf("Word \"%s\" cannot be placed\n", str);
			return 0;
		}
		slot = slot->next;
	}
	if (counter < limit) {
		printf("Not enough words\n");
		return 0;
	}
	return 1;
}

/*
 * Trying to place the given word into the crossword
 */
int placeWord(Slot *sl, char *crossword, int size, char *word) {
	int placed = 0;
	if (sl != NULL) {
		if (sl->length == (int)strlen(word)) {
			if (sl->direction == VERTICAL) placed = fitVertical(crossword, size, word, sl->x, sl->y, sl->length);
			else placed = fitHorizontal(crossword, size, word, sl->x, sl->y, sl->length);
		}
	}
	return placed;
}

/*
 * Check if the word fits horizontally in the crossword based on the already placed words starting from the position (x,y)
 * If the word fits, then it placed
 */
int fitHorizontal(char *crossword, int size, char *word, int x, int y, int length) {
	for (int i=0; i<length; i++)
		if (!isEmptyPos(crossword, size, x, y+i) && crossword[x*size + (y+i)] != word[i])
			return 0;
	for (int i=0; i<length; i++) crossword[x*size + (y+i)] = word[i];
	return 1;
}

/*
 * Check if the word fits vertically in the crossword based on the already placed words starting from the position (x,y)
 * If the word fits, then it placed
 */
int fitVertical(char *crossword, int size, char *word, int x, int y, int length) {
	for (int i=0; i<length; i++)
		if (!isEmptyPos(crossword, size, x+i, y) && crossword[(x+i)*size+y] != word[i])
			return 0;
	for (int i=0; i<length; i++) crossword[(x+i)*size+y] = word[i];
	return 1;
}

/*
 * Solve resursively the crossword without using the same word twice
 * For each word of the needed size, I try to place it. If I manage to place the word, I try to place the word in the next slot.
 * If I can't, I will return on the previous level and I change the word I placed
 * When the slot is null, which the next slot of the last, then we have a solve the crossword
 * When I try every possible word in the first slot and noone of them can lead to a crossword solution, then I can't find a solution
 */
int solve (char *crossword, int size, Slot *slot, DictList **dictionary) {
	if (slot != NULL) {
		char *prevCross = allocateCrossword(size);
		memcpy(prevCross, crossword, size*size*sizeof(char));
		DictNode *dn =  dictionary[slot->length]->first;
		while (dn != NULL) {
			if (!dn->used && placeWord(slot, crossword, size, dn->word)) {
				dn->used=1;
				if (solve(crossword, size, slot->next, dictionary)) {
					destroyCrossword(prevCross);
					return 1;
				}
				else {
					dn->used=0;
					memcpy(crossword, prevCross, size*size*sizeof(char));
				}
			}
			dn = dn->next;
		}
		destroyCrossword(prevCross);
		return 0;
	}
	else {
		return 1;
	}
}

/*
 * Prints the solution of the crossword, firstly the horizontal words and then the vertical, one word per line. 
 */
void printSolution (char *crossword, int size, SlotList *list) {
	char word[MAXWORD];
	Slot *slot = list->first;
	while (slot != NULL) {
		for (int i=0; i < slot->length; i++) {
			if (slot->direction == HORIZONTAL) word[i] = crossword[slot->x * size + (slot->y + i)];
			else word[i] = crossword[(slot->x + i)*size+slot->y];
		}
		word[slot->length] = '\0';
		printf("%s\n", word);
		slot = slot->next;
	}
}