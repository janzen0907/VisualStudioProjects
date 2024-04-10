#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_pointers.h"

#define BUFFER_SIZE 20

void testIntArray()
{
	int iArray[] = { 2, 7, 9 }; // initialize an int array using {}
	// Calculate the size of the array
	int iSize = sizeof(iArray) / sizeof(int);
	// Practice: Call a function named intArrayPrinter in a seperate source file named 
	// array_pointers.c (with an appropriate header file). The function should loop through the array
	// printing the value on a seperate line
	printf("The address of iAray in the calling function is \t%p\n", iArray);
	intArrayPrinter(iArray, iSize);
	intArrayPrinterWithPointer(iArray, iSize);
	
}

void testCharArrayPrinterWithPointer()
{
	// Write a function charArrayPrinterWithPointer in array_pointers.c
	// Use a pointer to move along one character at a time until you reach the
	// end of the string, dereferencing the pointer to display the character
	// at each location. You can use printf("%c", value); or putchar(value)
	charArrayPrinterWithPointer("Hello world!"); 
}

void testIntBytePrinter()
{
	int x = 2189640;
	intBytePrinter(x);
}

void testEncodeDecode()
{
	double x = encode();
	printf("%g\n", x); // %f is for a specific number of deciamls
	decode(x);
}

// First, have the user enter a string including spaces
// Then call a function called printStringsAsInts in array_pointers.c that will 
// take in a string and print it out as ints (in hex and in deciaml)
// Hint: look up the strlen (string length) function (google "Microsoft strlen")
// Consider what limitations your function might have. 
void testStringToInts()
{
	char cBuffer[BUFFER_SIZE];
	int iStringLength;
	
	// First, have the user enter a string including spaces
	// To get a string with spaces, we need to use gets or gets_s or fgets.
	// fgets gets a string from the designated input stream (could be a file or command line) up to the 
	// number of characters specifies or up to the newline but includes the newLine
	printf("Please enter a string to convert to integers:");
	//gets_s(cBuffer, BUFFER_SIZE);
	fgets(cBuffer, BUFFER_SIZE, stdin); // Stdin - Standard Input Stream

	// gets rid of the newLine
	iStringLength = strlen(cBuffer);
	// If it reads a string where the last character is a new line
	if (cBuffer[iStringLength - 1] == '\n')
	{
		// Replace the new line character with a null terminator
		cBuffer[iStringLength - 1] = '\0';
	}
	printStringsAsInts(cBuffer);
}

int main()
{
	//testIntArray();
	//testCharArrayPrinterWithPointer();
	//testIntBytePrinter();
	//testEncodeDecode();
	testStringToInts();

	return EXIT_SUCCESS;
}