#ifndef _slotList_
#define _slotList_

/* 
 * The position of the first letter of the word that I have to fill 
 */
typedef struct Slot {
	int x;					/* x position */
	int y;					/* y position */
	int length;				/* word's length that I have to fill */
	Direction direction;	/* horizontal/vertical */
	struct Slot *next;		/* next slot to fill */
} Slot;

/* List of slots */
typedef struct {
	Slot *first;	/* pointer to the first node of the list */
	Slot *last;		/* pointer to the last node of the list */
	int size;		/* list's size */
} SlotList;

SlotList *createSlotList(void);
void insertSlot(SlotList *, int, int, int, Direction);
void insertAtEnd(SlotList *, int, int, int, Direction);
void deleteFirstSlot(SlotList *);
void destroySlotList (SlotList *);
void printDirection(Direction);
void printSlot (Slot *);
void printSlotList (SlotList *);
SlotList* mergeLists(SlotList *, SlotList *);

#endif