#include <stdio.h>
#include <malloc.h> // Memory allocation - required for DMA
#include <string.h>
#include "dma.h"


// Function to print an array of ints
void printInts(int* iArrayPtr, int iSize)
{
	printf("The integers are: ");
	for (int i = 0; i < iSize - 1; i++)
	{
		printf("%d, ", *iArrayPtr);
		iArrayPtr++;
	}
	printf("%d\n", *iArrayPtr);
}

//This functionwill dynamically allocate
// space for a name of some MAX_NAME_SIZE plus an int for the SIN#, and ask
// the user to enter a name and an int for the SIN#, stored in the dynamically
// allocated space. getNameAndSIN() will return the dynamically allocated space.
char* getNameAndSIN()
{
	char* cNameAndSINPtr = malloc(MAX_NAME_SIZE * sizeof(char) + sizeof(int));
	int iLength;

	if (cNameAndSINPtr)
	{
		// Read in the name
		printf("Enter the name: ");
		fgets(cNameAndSINPtr, MAX_NAME_SIZE, stdin);

		// fgets puts in the newline character which we might not want
		// You can overwrite it with a null terminator
		iLength = strlen(cNameAndSINPtr);
		if (cNameAndSINPtr[iLength - 1] == '\n')
		{
			cNameAndSINPtr[iLength - 1] = '\0';
		}

		printf("Enter the SIN#: ");
		scanf_s("%d", (int*)cNameAndSINPtr + MAX_NAME_SIZE);
	}

	return cNameAndSINPtr;
}

void printNameAndSIN(char* cBuffer)
{
	int* iSINPtr = (int*)(cBuffer + MAX_NAME_SIZE);

	printf("The name is %s\n", cBuffer);
	printf("The SIN# is %d\n", *iSINPtr);
}


int* getInts(int iNumInts)
{
	/*
	Create memory space for the integers using the function malloc.
	malloc takes the size of memory in bytes as an argument.
	malloc returns a pointer to the first byte of the requested memory in the heap.
	malloc returns a (void*) void pointer, which is still a pointer,
	just no associated type. Usually a cast is required.
	The contents of the newly allocated block of memory are not initialized
	(use memset if you want - memset is a function that initializes a block of memory).
	*/
	int* iBufferPtr = (int*)malloc(iNumInts * sizeof(int));
	//memset(iBufferPtr, 0, iNumInts * sizeof(int));

	if (iBufferPtr != NULL) // malloc will return NULL if unsuccessful
	{
		// Load data into the array
		for (int i = 0; i < iNumInts; i++)
		{
			printf("Enter integer %d: ", (i + 1));
			scanf_s("%d", iBufferPtr + i);
		}
	}

	return iBufferPtr;
}


// Add an int to the end of a dynamic array
// Purpose --> Takes an array, increases its size by one. Asks the user for an int
//				and adds it to the end.
// iArrayPtr --> The original dynamically allocated array
// iSizePtr --> Pointer to the original size of the array.
//				Used to increase the passed-in size.
// Note: The array originally passed in is freed after its contents are copied.
int* addInt(int* iArrayPtr, int* iSizePtr)
{
	// Create a new array
	int* iNewPtr = (int*)malloc((*iSizePtr + 1) * sizeof(int));

	// Copy the data from the old array to the new array using the memcpy function
	memcpy(iNewPtr, iArrayPtr, (*iSizePtr) * sizeof(int));

	// Free the original array. If we don't, we are creating a "memory leak".
	// Eventually, memory leaks can cause a system to slow down or crash
	free(iArrayPtr);
	iArrayPtr = NULL;

	// Add new int to the end of the new array
	printf("Enter another integer: ");
	scanf_s("%d", iNewPtr + *iSizePtr);

	// Increment the size
	(*iSizePtr)++;

	return iNewPtr;
}


// Add an int to the end of a dynamic array using realloc (C89)
int* addIntRealloc(int* iArrayPtr, int* iSizePtr)
{
	// Reallocates the area of memory by expanding/contracting the old block
	// or allocating a new memory block and freeing the old block
	int* iNewPtr = (int*)realloc(iArrayPtr, (*iSizePtr + 1) * sizeof(int));

	if (iNewPtr != NULL)
	{
		// Add new int to the end of the new array
		printf("Enter another integer: ");
		scanf_s("%d", iNewPtr + *iSizePtr);

		// Increment the size
		(*iSizePtr)++;
	}
	else
	{
		iNewPtr = iArrayPtr;
	}

	return iNewPtr;
}


// Return a pointer to a dynamically allocated string or NULL if it fails
char* getStringDynamic(const char* cPrompt)
{
	// Pointer to a dynamically allocated string
	char* cTempPtr = NULL;
	// Pointer to a dynamically allocated string of exact size required
	char* cReturnPtr = NULL;
	int iSizeDestination = 0;

	cTempPtr = (char*)malloc(MAX_STRING_SIZE * sizeof(char));

	// If memory was allocated (malloc can fail, and if it does, it returns NULL)
	if (cTempPtr) // same as (cTempPtr != NULL)
	{
		// Prompts the user for a string
		printf("%s", cPrompt);
		// Scan in the string using gets_s
		gets_s(cTempPtr, MAX_STRING_SIZE);

		// Allocate a new buffer based on the actual size of the input
		// Always remember to allocate space for the null terminator
		iSizeDestination = strlen(cTempPtr) + 1;
		cReturnPtr = (char*)malloc(iSizeDestination * sizeof(char));

		if (cReturnPtr)
		{
			// Copy the data from temp array to return array
			strcpy_s(cReturnPtr, iSizeDestination, cTempPtr);
		}

		free(cTempPtr);
		cTempPtr = NULL;
	}

	return cReturnPtr;
}

char* concatenateString(const char* cStringPtr1, const char* cStringPtr2)
{
	int iLengthFirst = strlen(cStringPtr1);
	int iLengthSecond = strlen(cStringPtr2);
	char* cReturnString = (char*)malloc(iLengthFirst + iLengthSecond + 1);

	if (cReturnString)
	{
		// Just to be safe, initalize the string to empty
		cReturnString[0] = '\0';

		// Copy the first string to destination
		strcpy_s(cReturnString, iLengthFirst + 1, cStringPtr1);

		// Copy the second string to the end of the first string
		// Either method can be used strcat just adds it to the end where as strcpy
		// strcat_s(cReturnString, iLengthFirst + iLengthSecond + 1, cStringPtr2);
		strcpy_s(cReturnString + iLengthFirst, iLengthSecond + 1, cStringPtr2);
	}
}
