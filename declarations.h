#ifndef _declarations_
#define _declarations_

#define ROWSIZE 10	/* Maximum amount of characters in each line of grid file */
#define MAXWORD 127	/* Maximum word's size */

/* Direction to fill a word in the crossword */
enum Direction {HORIZONTAL=0, VERTICAL}; 
typedef enum Direction Direction;

#endif