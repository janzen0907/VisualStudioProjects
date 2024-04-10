#include <stdio.h>
#include <stdlib.h>
#include "array_pointers.h"
#include <string.h>

#define BUFFER_SIZE 20

	// Practice: Call a function named intArrayPrinter in a seperate source file named 
	// array_pointers.c (with an appropriate header file). The function should loop through the array
	// printing the value on a seperate line
void intArrayPrinter(int iArrayPtr[], int iSize)
{
	printf("The address stored in iArrayPtr in the function is \t%p\n", iArrayPtr);
	printf("The address of iArrayPtr in the function is \t\t%p\n", &iArrayPtr);

	for (int i = 0; i < iSize; i++)
	{
		printf("The loop counter is %d and the array value is %d"
			" and the value's address is %p\n",
			i, iArrayPtr[i], &iArrayPtr[i]);
	}
	printf("\n");
}

void intArrayPrinterWithPointer(int* iArrayPtr, int iSize)
{
	for (int i = 0; i < iSize; i++)
	{
		// To retrieve the value where the pointer points, we "dereference" it
		// using the dereference operator *
//		printf("The loop counter is %d and the array value is %d"
//			" and the value's address is %p\n",
//			i, *(iArrayPtr + i), iArrayPtr + i);
		// The notation *(iArrrayPty +i) is exaclty the same as iArrayPtr[i]
		// Note that because iArrayPtr is int*, we add i * sizeof(int) each time
	
		// You could also "walk" the pointer through the array
		printf("The loop counter is %d and the array value is %d"
						" and the value's address is %p\n",
					i, *iArrayPtr, iArrayPtr);
		iArrayPtr++; // increment iArrayPtr by sizeof(int), so move to next array element
	}
	// The pointer will point past the end of the array whent the loop is complete
	printf("The final value of iArrrayPtr is %p\n", iArrayPtr);
}

// Write a function charArrayPrinterWithPointer in array_pointers.c
	// Use a pointer to move along one character at a time until you reach the
	// end of the string, dereferencing the pointer to display the character
	// at each location. You can use printf("%c", value); or putchar(value)
void charArrayPrinterWithPointer(char* cArrayPtr)
{
	printf("The address of cArrayPtr is \t%p\n", &cArrayPtr);
	// Note that the string literal is stored in the text segment (also where the function is)
	printf("The address of string literal in cArrayPtr is \t%p\n", cArrayPtr);
	printf("The character at the address in cArrayPty is \t%x\n", *cArrayPtr);
	printf("The address of charArrayPrinterWithPointer function is \t%p\n", charArrayPrinterWithPointer);

	// Try to write to th estring literal (that is, the text segment)
//	*cArrayPtr = 'A';
	// Cannot do this - you should never try to alter data in the text segment

	//while (*cArrayPtr != '\0')
	//{
	//	printf("%c", *cArrayPtr);
	//	cArrayPtr++;
	//}
	//printf("\n");

	while (*cArrayPtr)
	{
		putchar(*cArrayPtr++);
		// putchar outputs a character to stdout
		// ++ operates on the cArrayPtr because of the order of operations
		// but we dereference it before adding 1 because it is post-increment
		// https://en.cppreference.com/w/c/language/operator_precedence
		// ++ moves to the next char because cArrayPtr is char*.

	}
	putchar('\n');
}

void intBytePrinter(int iValue)
{
	printf("The int in hex is %x\n", iValue);

	// With a char pointer, we can work one byte at a time
	char* cPtr = (char*) & iValue;

	for (int i = 0; i < sizeof(int); i++)
	{
		printf("The byte value is %x and the character equivalent is %c\n", *cPtr, *cPtr);
		cPtr++;
	}

}

// Encode some data into a double. the double is just an 8-byte buffer in this case
// We will store a 3-letter name, an age in one byte, followed by a student loan amount
// in two bytes
double encode()
{
	// Allocate the buffer
	double x = 0.0; // double is 8 bytes of memory
	unsigned char* cNamePtr = (unsigned char*)&x; // storing the address of the value x

	// Prompt the user for input
	printf("Enter a 3-letter name: ");
	scanf_s("%3s", cNamePtr, NAME_SIZE);

	//Enter an age
	printf("Enter an age (less than 255): ");
	scanf_s("%hhu", (unsigned char*)(cNamePtr + NAME_SIZE));

	// Enter the student loan amount
	printf("Enter your student loan as an integer <= 65535: ");
	scanf_s("%hu", (unsigned short*)(cNamePtr + NAME_SIZE + AGE_SIZE));

	return x;
}

void decode(double x)
{
	// Pointer to the name
	unsigned char* cNamePtr = (unsigned char*)&x;
	unsigned short* loanPtr = (unsigned short*)(cNamePtr + NAME_SIZE + AGE_SIZE);

	// Print the the string
	printf("The name is %s\n", cNamePtr);
	// Dereference the pointer to retrieve teh single byte representing the age
	printf("The age is %d\n", (*cNamePtr + NAME_SIZE));
	// Print the student loan
	printf("The student loan is %hu\n", *loanPtr);

}


// Then call a function called printStringsAsInts in array_pointers.c that will 
// take in a string and print it out as ints (in hex and in deciaml)
// Hint: look up the strlen (string length) function (google "Microsoft strlen")
// Consider what limitations your function might have.
void printStringsAsInts(char* cStringToConvert)
{
	int iStringSize = strlen(cStringToConvert) + 1; // add 1 for null terminator
	int iNumInts = iStringSize / sizeof(int); // number of ints using integer division
	int i;
	// We need an integer pointer that will point to the same address as the char pointer
	int* iPtr = (int*)cStringToConvert; // integer pointer to the start of string

	int iRemainingBytes = iStringSize % sizeof(int); // bytes left after integer division
	int iNewInt = 0; // contains last int with bytes left after integer division
	// We need a char pointer at this point to hold the left over char
	char* cLastBytesPtr = NULL;
	char* cBuildIntPtr = NULL;


	printf("Length of string to convert is: %d\n",  iStringSize);
	printf("It contains %d ints\n ", iNumInts);
	printf("'%s' converted to integers is: \n", cStringToConvert);

	for (i = 0; i < iNumInts; i++)
	{
		// Dereferance the pointer and walk thoruhg it
		printf("In hex: %x \t In decimal: %d\n", *iPtr, *iPtr); // or could use iPtr[i] without walking the pointer
		intBytePrinter(*iPtr); // to see if it is converted properly
		iPtr++; // at this point iPtr is pointing at the last int

	}

	// Limitation of above: only pritns out 4-byte chunks.
	// What if the string isn't evenly divisible by 4?
	// Can't just print another int - could exceed buffer space
	// or go into undefined characters
	// Could build another int as follows:
	if (iRemainingBytes > 0)
	{
		cLastBytesPtr = (char*)iPtr; // char pointer to bytes remaining after the above loop
		cBuildIntPtr = (char*) &iNewInt; // Point to new integer to build that integer

		for (i = 0; i < iRemainingBytes; i++)
		{
			// Take the byte from cLastBytesPointer and put it into the intPtr
			*cBuildIntPtr = *cLastBytesPtr; // Add remaining byte to new integer
				// Move to the next byte
			cLastBytesPtr++;
			cBuildIntPtr++;
		}
		printf("%x \t%d\n", iNewInt, iNewInt);
		intBytePrinter(iNewInt);

	}

}
