/*
	Filename:	functions.c
	Author:		Sample Solution
	Course:		COSC 292 (Advanced Programming 2)
	Instructor:	Michael Grzesina
	Date:		Winter 2024
	Purpose:	Utility functions for practice using pointers and arrays in C
*/

#include <stdio.h>
#include "functions.h"


/*
	Function:		swap
	Purpose:		swaps the values of the integers pointed to by the parameters
	Parameters:		p1 - the address of the first integer to be swapped
					p2 - the address of the second integer to be swapped
	Returns:		nothing
	Changes:		The values of the integers addressed by p1 and p2 are swapped
	Assumptions:	none
*/
void swap(int* p1, int* p2)
{
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}


/*
	Function:		newInteger
	Purpose:		declare and initialize an integer inside the function and return the address of that integer
	Parameters:		none
	Returns:		the address of an integer declared within the function
	Assumptions:	none
*/
int* newInteger()
{
	int i = 123456789;

	return &i;
}


/*
	Function:		hideString
	Purpose:		hides a given 4-character string in the third byte of the given integer array
	Parameters:		iArrPtr - the address of an array of 4 integers
					cArrPtr - the address of a 4-character string
	Returns:		Nothing
	Changes:		The values of iArrPtr are changed by making each integer's 3rd byte equal to a character from cArrPtr
	Assumptions:	There are 4 characters in cArrPtr (not necessarily including the null terminator)
					iArrPtr is of (at least) size 4
					ints are of size 4
*/
void hideString(int* iArrPtr, char* cArrPtr)
{
	// Create a char pointer and initialize to NULL (0) for safety.
	char* cPtr = NULL;

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		// Set the pointer to the address of the given integer
		cPtr = (char*)&iArrPtr[i]; // or (char*)(iArrPtr + i);
		// Walk pointer up to 3rd byte of int
		cPtr += 2;
		// Set value
		*cPtr = cArrPtr[i]; // or *cArrPtr++
	}
}


/*
	Function:		unHideString
	Purpose:		displays a given 4-character string in the third byte of the given integer array
	Parameters:		iArrPtr - the address of an array of 4 integers whose 3rd bytes are characters
	Returns:		Nothing
	Assumptions:	iArrPtr is of (at least) size 4 and the 3rd byte of each integer contains a hidden character
					ints are of size 4
*/
void unHideString(int* iArrPtr)
{
	// Create a char pointer and point it to iArrPtr
	char* cPtr = (char*)iArrPtr;
	// Walk pointer up to the 3rd byte of the int
	cPtr += 2;

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		// Print the current character
		printf("%c", *cPtr);
		// Walk the pointer to the next hidden character
		cPtr += 4;

		// or
//		cPtr = (char*)&iArrPtr[i];
//		printf("%c", *(cPtr + 2));
	}
	printf("\n");
}
