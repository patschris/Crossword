#ifndef _crossword_
#define _crossword_

char *allocateCrossword (int);
void fillBlackCells (FILE *, char *, int);
void printCrossword (char *, int);
void destroyCrossword (char *);

#endif