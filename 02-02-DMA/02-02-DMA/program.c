#include <stdlib.h>
#include <stdio.h>
#include "dma.h"


// for detecting memory leaks
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


void testIntDMA()
{
	int iSize = 3;
	int* iBufferPtr = getInts(iSize);

	printInts(iBufferPtr, iSize);

	// Demo a buffer overflow.
	// C allows us to overflow the buffer, creating potential errors and security
	// vulnerabilities. It is up to the programmer to ensure that you never go beyond
	// the bounds of the buffer.
//	iBufferPtr[6] = 9;
//	printInts(iBufferPtr, iSize + 3);

	// Add another int to the array
	iBufferPtr = addInt(iBufferPtr, &iSize);
	iBufferPtr = addIntRealloc(iBufferPtr, &iSize);
	printInts(iBufferPtr, iSize);

	// Once we're done with dynamically allocated memory,
	// free it using the function free().
	// Otherwise, we create a "memory leak".
	free(iBufferPtr);
	// Note that the pointer still points to the memory that was allocated
//	printInts(iBufferPtr, iSize);
	// If you want to erase data, call memset BEFORE freeing the memory

	// After you free the memory, set the pointer to NULL
	iBufferPtr = NULL;
	//	printInts(iBufferPtr, iSize); // will crash the program if we try to access null ptr.
}


void testDynamicString()
{
	char* cFirstPtr = NULL;
	char* cLastPtr = NULL;

	cFirstPtr = getStringDynamic("Enter first name: ");
	cLastPtr = getStringDynamic("Enter last name: ");

	if (cFirstPtr)
	{
		printf("The first name is %s\n", cFirstPtr);
		free(cFirstPtr);
		cFirstPtr = NULL;
	}
	if (cLastPtr)
	{
		printf("The last name is %s\n", cLastPtr);
		free(cLastPtr);
		cLastPtr = NULL;
	}
}


void testNameAndSIN()
{
	// Create a function named getNameAndSIN() that will dynamically allocate
	// space for a name of some MAX_NAME_SIZE plus an int for the SIN#, and ask
	// the user to enter a name and an int for the SIN#, stored in the dynamically
	// allocated space. getNameAndSIN() will return the dynamically allocated space.
	// Call getNameAndSIN().
	char* cBuffer = getNameAndSIN();


	// Create a function named printNameAndSIN() that will print out the name and the
	// SIN#, assuming that the name is stored in a space of MAX_NAME_SIZE and the
	// SIN# is stored in the int following that space.
	// Call printNameAndSIN().
	// Handle dynamically allocated memory appropriately.
	if (cBuffer)
	{
		printNameAndSin(cBuffer);
		free(cBuffer);
		cBuffer = NULL;
	}
}

void testStringConcatenate()
{
	char* cResultString = concatenateString("Hello", "world ");
	if (cResultString)
	{
		printf("%s", cResultString);
		free(cResultString);
		cResultString = NULL;
	}
}





int main()
{
	//int iArray[] = { 10, 20, 30 };

	//printInts(iArray, sizeof(iArray) / sizeof(int));
	//testIntDMA();
	//testDynamicString();
	//testNameAndSIN();
	testStringConcatenate();

	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
}
