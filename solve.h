#ifndef _solve_
#define _solve_

int isEmptyPos (char *, int, int, int);
void findHorizontalSlots (SlotList *, char *, int, int);
void findVerticalSlots (SlotList *, char *, int, int);
int checkSolution (SlotList *, DictList **, char *, int);
int placeWord(Slot *, char *, int, char *);
int fitHorizontal(char *, int, char *, int, int, int);
int fitVertical(char *, int, char *, int, int, int);
int solve (char *, int, Slot *, DictList **);
void printSolution (char *, int, SlotList *);

#endif