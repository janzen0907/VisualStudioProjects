#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include <string.h>
// argc is the number of command lines arguements

/*
* Purpose: Trim a number of characters from the right end of the dynamically 
*	allocated string passed in
* cPtrToPtr --> a pointer to a pointer taht points to a string
*	pointer to the string will be changed
* iNumChars --> The number of characters to chop the right end of the string
*/
void trimRight(char** cPtrToPtr, int iNumChars)
{

	int iDiff = 0;

	// Create a temp pointer to the original array
	char* cOriginalPtr = *cPtrToPtr; // dereferancing a pointer to a pointer gives us a pointer
	printf("Address in cOriginalPtr is %p\n", cOriginalPtr);
	printf("Address n cPtrToPtr is %p\n\n", cPtrToPtr);


	// Difference in size of the new and old string
	iDiff = strlen(cOriginalPtr) - iNumChars; // could check to make sure this is a non-negative num

	// Allocate space for the new array
	*cPtrToPtr = (char*)malloc((iDiff + 1) * sizeof(char));

	// Copy the data from teh old string to the new string
	memcpy(*cPtrToPtr, cOriginalPtr, iDiff * sizeof(char));

	// Add the null terminator to the end of the new sting
	*(*cPtrToPtr + iDiff) = '\0'; // double de refernce - character at the pointer pointer to 

	// Free the old string
	free(cOriginalPtr);
	cOriginalPtr = NULL;

}


void testTrimRight()
{
	char cArray[] = "Michael";
	// Allocate dynamic memory that is the same size as the string
	char* cPtr = (char*)malloc((strlen(cArray) + 1) * sizeof(char));
	strcpy(cPtr, cArray);

	printf("cPtr %s\n", cPtr);
	printf("The address stored by cPtr is %p\n", cPtr);
	printf("The address of cPtr is %p\n\n", &cPtr);

	// Take the string at c pointer and trim off the 3 last spaces on the right 
	trimRight(&cPtr, 3);

	printf("cPtr is now: %s\n", cPtr);

	free(cPtr);
	cPtr = NULL;
}


// Write a function findChar that takes a string and a char to find in the string
// The function will also take a pointer to a pointer to which the function will 
// assign the address of the first instance of the char in the string. If not found in the string
// the pointer will be assigned NULL. The function will also return the number of chars into teh string that the
// char was found, or -1 if not found
int findChar(char* cStringPtr, char cCharToFind, char** cPtrPtr)
{
	int location = 0;

	while (*cStringPtr) // != '\0'
	{
		if (*cStringPtr == cCharToFind)
		{
			*cPtrPtr = cStringPtr;
			return location;
		}
		location++;
		cStringPtr++;
	}

	*cPtrPtr = NULL;
	return -1;
}

void testFindChar()
{
	char cArray[] = "Coralee";
	char* cAddressOfChar;

	int index = findChar(cArray, 'e', &cAddressOfChar);

	printf("Index of character = %d\n", index);
	printf("The address of cArray is %p\n", cArray);
	printf("The address of the character is %p\n", cAddressOfChar);
}

char* allocateRow(int iRowSize)
{
	char* cPtr = (char*)malloc(iRowSize * sizeof(char));
	cPtr[0] = '\0';
	
	return cPtr;
}

// Return a dynamically allocated 2-D jagged array based on inforamtion passed in
// iRowSizes --> array of the size of each row
// iNumRows --> number of rows
char** createJaggedArray(int iRowSizes[], int iNumRows)
{
	// Need a pointer to an array of pointers
	char** cPtrPtr = (char*)malloc(iNumRows * sizeof(char*));
	
	// Create each row
	for (int i = 0; i < iNumRows; i++)
	{
		
		cPtrPtr[i] = allocateRow(iRowSizes[i]);
	}


	return cPtrPtr;
}

void printArrayOfStrings(char** cPtrPtr, int iRows)
{
	for (int i = 0; i < iRows; i++)
	{
		printf("String %d is : %s\n", i, cPtrPtr[i]);
	}
}

void testJaggedArray()
{
	int iRowValues[] = { 4, 6, 5 };
	// calculate the number of rows in iRowValues
	int iRows = sizeof(iRowValues) / sizeof(int);

	// Create the jagged array
	char** cPtrPtr = createJaggedArray(iRowValues, iRows);
	
	// Add some data to each row
	// Index into each location char by char using brackets
	cPtrPtr[0][0] = 'M';
	cPtrPtr[0][1] = 'e';
	cPtrPtr[0][2] = 'l';
	cPtrPtr[0][3] = '\0';

	// index in using pointer math
	*(*(cPtrPtr + 1) + 0) = "C";
	*(*(cPtrPtr + 1) + 1) = "h";
	*(*(cPtrPtr + 1) + 2) = "r";
	*(*(cPtrPtr + 1) + 3) = "i";
	*(*(cPtrPtr + 1) + 4) = "s";
	*(*(cPtrPtr + 1) + 5) = "\0";

	// Use strcpy - only because this is a jagged array of chars
	strcpy(cPtrPtr[2], "Mark");

	printArrayOfStrings(cPtrPtr, iRows);

	// Free all the memory created for the jagged array
	// Free each row first
	for(int i = 0; i < iRows; i++)
	{
		free(cPtrPtr[i]);
		cPtrPtr[i] = NULL;
	}
	free(cPtrPtr);
	cPtrPtr = NULL;
}

int* getDynamicDoubles()
{
	printf("Input a number of doubles");
	int iNumDoubles = scanf("%lf");
	

}

void testDoubleArrrayWithMax()
{
	// Create a function  getDynamicDoubles that asks the user for a number of doubles
	// and read in that number of doubles ("%lf in scanf) into a dynamically 
	// allocated array and return that array
	// Also change an int so that it wil contain the size of the array allocated.
	// 
	// Also change a pointer so that it will point ot the largest element in that array
	// In this function (calling function), print out the array
	// and then print out the max value
}



void testSwapBytesWithPointers()
{
	// Create a function swapBytesWithPointers that will take an int and swap its 
	// bytes (as if it Big-Endian instead of Little-Endian) and change a char
	// pointer to the new high-order byte (formally the low-order byte). For instance, 
	// if 0x6566678 was passed in, the result would be
	// 0x6867665 anad the pointer would point to the byte containing 0x68.
}

int main(int argc, char** argv[])
{
	//printf("There are %d command-line arguments\n", argc);
	//printf("argv is \t%p\n", argv);
	//for (int i = 0; i < argc; i++)
	//{
		//printf("%p\t%p\t%c\t%s\n", argv + i, argv[i], argv[i][0], argv[i]);
	//}

	//testTrimRight();
	//testFindChar();
	testJaggedArray();
	//testDoubleArrayWithMax();

}