#ifndef DMA_H
#define DMA_H

#define MAX_STRING_SIZE	255
#define MAX_NAME_SIZE	30

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

// A function that creates a buffer with a name (MAX_NAME_SIZE) and SIN#
char* getNameAndSIN();

// Print the name and the SIN of the user
void printNameAndSIN(char* cBuffer);

// funciton to conacatenate two strings. No memory is freed within the function
// Returns a dynamically allocated string
char* concatenateString(const char* cString1, const char* cString2);




#endif // !DMA_H
