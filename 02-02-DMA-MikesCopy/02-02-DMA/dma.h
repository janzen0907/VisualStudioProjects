#ifndef DMA_H
#define DMA_H

#define MAX_STRING_SIZE	255

// Function to print an array of ints
void printInts(int* iArrayPtr, int iSize);

// Return an array of ints that are dynamically allocated
int* getInts(int iNumInts);

// Add an int to the end of a dynamic array
int* addInt(int*, int*);

// Add an int to the end of a dynamic array using realloc (C89)
int* addIntRealloc(int*, int*);

// Return a pointer to a dynamically allocated string or NULL if it fails
char* getStringDynamic(const char* cPrompt);

#endif // !DMA_H
