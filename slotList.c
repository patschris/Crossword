#include <stdio.h>
#include <stdlib.h>
#include "declarations.h"
#include "slotList.h"

/*
 * Creation and initialization of the list that contains slots
 */
SlotList *createSlotList() {
	SlotList *l;
	if ((l= (SlotList *)malloc(sizeof(SlotList))) == NULL) {
		perror("SlotList malloc failed");
		exit(-1);
	}
	l->first = NULL;
	l->last = NULL;
	l->size = 0;
	return l;
}

/*
 * Insert to list using insertion sort based in word's length
 * https://www.geeksforgeeks.org/insertion-sort-for-singly-linked-list/
 */
void insertSlot(SlotList *l, int x, int y, int length, Direction dir) {
	Slot *s;
	if ((s = (Slot *)malloc(sizeof(Slot)))== NULL) {
		perror("Slot malloc failed");
		exit(-1);
	}
	s->x = x;
	s->y = y;
	s->length = length;
	s->direction = dir;
	if (l->size == 0) {
		l->first = s;
		l->last = s;
		s->next = NULL;
	}
	else {
		if (l->first->length < s->length) {
			s->next = l->first;
			l->first = s;
		}
		else {
			Slot *cur = l->first;
			while (cur->next != NULL && cur->next->length > s->length) {
				cur = cur->next;
			}
			s->next = cur->next;
			cur->next = s;
			if (s->next == NULL) l->last = s;
		}	
	}
	l->size++;
}

/*
 * Insert at the end of the list
 */
void insertAtEnd(SlotList *sl, int x, int y, int length, Direction dir) {
	Slot *s;
	if ((s = (Slot *)malloc(sizeof(Slot)))== NULL) {
		perror("Slot malloc failed");
		exit(-1);
	}
	s->x = x;
	s->y = y;
	s->length = length;
	s->direction = dir;
	s->next = NULL;
	if (sl->size == 0) {
		sl->first = s;
		sl->last = s;
	}
	else {
		sl->last->next = s;
		sl->last = s;
	}
	sl->size++;
}

/*
 * Delete the first node of the list
 */
void deleteFirstSlot(SlotList *l) {
	Slot *temp = l->first;
	if (l->first!=NULL) {
		l->first = l->first->next;
		free(temp);
	}
	l->size--;
}

/*
 * Destroying the list by deleting all the nodes
 */
void destroySlotList (SlotList *l) {
	while (l->size) deleteFirstSlot(l);
	free(l);
}

/*
 * Prints the enum Direction
 */
void printDirection(Direction d) {
	if (d == HORIZONTAL) printf("HORIZONTAL\n");
	else if (d == VERTICAL) printf("VERTICAL\n");
	else printf("UNSPECIFIED\n");
}

/*
 * Print a slot (list's node)
 */
void printSlot (Slot *s) {
	printf("(%d,%d) --> %d chars --> ", s->x, s->y, s->length);
	printDirection(s->direction);
}

/*
 * Print all the list's nodes
 */
void printSlotList (SlotList *l) {
	Slot *temp = l->first;
	while (temp != NULL) {
		printSlot(temp);
		temp = temp->next;
	}
}

/*
 * Merge two lists and produces a new one
 */
SlotList *mergeLists(SlotList *hor, SlotList *ver) {
	int counter = 0;
	SlotList *merged = createSlotList();
	while (hor->size > 0 || ver->size > 0) {
		counter++;
		if (counter%2) {
			if (hor->first != NULL) {
				insertAtEnd(merged, hor->first->x, hor->first->y, hor->first->length, hor->first->direction);
				deleteFirstSlot(hor);
			}
		}
		else {
			if (ver->first != NULL) {
				insertAtEnd(merged, ver->first->x, ver->first->y, ver->first->length, ver->first->direction);
				deleteFirstSlot(ver);
			}
		}
	}
	destroySlotList(hor);
	destroySlotList(ver);
	return merged;
}