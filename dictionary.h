#ifndef _dictionary_
#define _dictionary_ 

FILE *openDictionary (char *);
void readDictionary (FILE *, DictList ***);
void destroyDictionary (DictList **);
void printDictionary(DictList **);

#endif