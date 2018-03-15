#ifndef _dictList_
#define _dictList_

/* Dictionary's node */
typedef struct DictNode {
	int used;					/* if the word is used in the solution set */
	char word[MAXWORD];			/* word written from the txt file */
	struct DictNode *next;		/* pointer to the next node */
} DictNode;

/* Dictionary list. Holds words of the same size */
typedef struct {
	DictNode *first;	/* pointer to the first node of the list */
	DictNode *last;		/* pointer to the last node of the list */
	int size;			/* list's size */
} DictList;

DictList *createDictList(void);
void insertDictNode(DictList *, char *);
void deleteFirstDictNode (DictList *);
void destroyDictList (DictList *);
void printDictList (DictList *);
int searchWord (DictList *, char *);

#endif