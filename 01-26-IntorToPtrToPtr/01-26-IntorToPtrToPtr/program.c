#include <stdio.h>
#include <stdlib.h>

// Pointers store an address
// Pointers are also stored in memory, so they have an address
// Thus, we can store a pointer to a pointer (which stores the address of a pointer)

// Let's start by looking at a function that doesn't return a pointer
/*
* Function: myIndexOf
* Purpose: return the position of the first occurrence of a character passed in
*	or -1 if the character is not found
* Parameters cPtr - pointer to the string to find the character in
*		     cSeek - character to find
* Returns:	the position of the character in the string, or -1 if not found
* Assumptions: cPtr is a null-terminated string
*/
int myIndexOf(const char* cPtr, char cSeek)
{
	int iLocation = 0;
	while (*cPtr)
	{
		if (*cPtr == cSeek)
		{
			return iLocation;
		}
		cPtr++;
		iLocation++;
	}
	return -1;
}

// Let's do a function that will require using a pointer's value
/*
* Function:	myIndexOfAndCount
* Purpose:	return the location of the first occurrence of a given character in
*	a given string, and change the count whose address is apssed in to the count
*	of the given character in teh given string
* Parameters:	cPtr - string to find the character in
*				cSeek - character to be found
*				iCountPtr - address of teh count to be updated
* Returns:	The first position of the character to be found or -1
* Changes:	The int at iCountPtr to the number of occurrences of the character
*/
int myIndexAndCount(const char* cPtr, char cSeek, int* iCountPtr)
{
	int iLocation = -1;
	int iPosition = 0;

	*iCountPtr = 0;

	while (*cPtr)
	{
		if (*cPtr == cSeek)
		{
			if (iLocation == -1)
			{
				iLocation = iPosition;
			}
			// We need it to in brackets here or else it will increase the location of the pointer
			(*iCountPtr)++;
		}
		cPtr++;
		iPosition++;
	}
	printf("In the function, count is %d\n", *iCountPtr);
	return iLocation;
}

// Function that will use a pointer to a pointer
/*
* Function:	myIndexOfAndCountAndLastPosition
* Purpose:	return the location of the first occurrence of a given character in
*	a given string, and change the count whose address is apssed in to the count
*	of the given character in teh given string, and change the pointer whose
*	address is passed in to the position of the last charater found
* Parameters:	cPtr - string to find the character in
*				cSeek - character to be found
*				iCountPtr - address of teh count to be updated
*				cPtrToPtr - address of the pointer to be updated
* Returns:	The first position of the character to be found or -1
* Changes:	The int at iCountPtr to the number of occurrences of the character
*			The pointer at cPtrToPtr to the address of the last occurence or NULL
*/

int myIndexOfAndCountAndLastPosition(const char* cPtr, char cSeek, int* iCountPtr,
	char** cPtrToPtr)
	// char ** takes in the address to a pointer than a pointer
{
	int iLocation = -1;
	int iPosition = 0;

	*iCountPtr = 0;
	*cPtrToPtr = NULL;

	while (*cPtr)
	{
		if (*cPtr == cSeek)
		{
			if (iLocation == -1)
			{
				iLocation = iPosition;
			}
			// We need it to in brackets here or else it will increase the location of the pointer
			(*iCountPtr)++;

			// This will give us the pointer that we want to change in the calling function to the value
			// we want to change it to
			*cPtrToPtr = cPtr;

		}
		cPtr++;
		iPosition++;
	}
	printf("In the function, count is %d\n", *iCountPtr);
	if (*cPtr != NULL)
	{
		printf("In the function, the character pointed at is %c\n", **cPtrToPtr);
	}
	
	return iLocation;
}

int main()
{
	char cTestString[] = "It's a beautiful day, isn't it?";
	int iLocation;
	int iCount = 0;
	// scanf("%d", &iCount); if we wanted to alter something passed in by the user do this
	char* cPtr = NULL;

	printf("Address of cTestString is %p\n\n", cTestString);


	iLocation = myIndexOf(cTestString, '?');
	// We need to pass in the address of iCount or else it will not be changed outside of the function
	
	iLocation = myIndexAndCount(cTestString, 't', &iCount);
	printf("The position of the character is %d\n", iLocation);
	printf("The count of the character is %d\n\n", iCount);

	iLocation = myIndexOfAndCountAndLastPosition(cTestString, 'a', &iCount, &cPtr);
	printf("The position of the character is %d\n", iLocation);
	printf("The count of the character is %d\n\n", iCount);
	printf("The character at thte given location is %c\n", *cPtr);

	return EXIT_SUCCESS;
}
