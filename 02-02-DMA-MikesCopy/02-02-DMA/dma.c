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
