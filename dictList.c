#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"
#include "dictList.h"

/*
 * Creation and initialization of the list that contains dictionary nodes
 */
DictList *createDictList() {
	DictList *l;
	if ((l = (DictList *)malloc(sizeof(DictList))) == NULL) {
		perror("DictList malloc failed");
		exit(-1);
	}
	l->first = NULL;
	l->last = NULL;
	l->size = 0;
	return l;
}

/*
 * Insert at the end of the list
 */
void insertDictNode(DictList *l, char *str) {
	DictNode *n;
	if ((n = (DictNode *)malloc(sizeof(DictNode))) == NULL) {
		perror("DictNode malloc failed");
		exit(-1);
	}
	strcpy(n->word, str);
	n->used = 0;
	n->next=NULL;
	if (l->size) l->last->next = n;
	else l->first = n;
	l->last = n;
	l->size++;
}

/*
 * Delete the first node of the list
 */
void deleteFirstDictNode (DictList *l) {
	DictNode *temp = l->first;
	if (l->first!=NULL) {
		l->first = l->first->next;
		free(temp);
	}
	l->size--;
}

/*
 * Destroying the list by deleting all the nodes
 */
void destroyDictList (DictList *l) {
	while (l->size) deleteFirstDictNode(l);
	free(l);
}

/*
 * Print all the list's nodes
 */
void printDictList (DictList *l) {
	DictNode *temp = l->first;
	printf("List size = %d\n", l->size);
	while (temp != NULL) {
		printf("%s is ", temp->word);
		if (temp->used) printf("used\n");
		else printf("not used\n");
		temp = temp->next;
	}
}

/*
 * Search if the dictionary contains the given word
 */
int searchWord (DictList *l, char *str) {
	DictNode *temp = l->first;
	while (temp != NULL) {
		if (!strcmp(temp->word, str)) return 1;
		temp = temp ->next;
	}
	return 0;
}