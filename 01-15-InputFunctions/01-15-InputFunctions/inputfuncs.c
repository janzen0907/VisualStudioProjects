#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // contains all of the string functions in C

// Note the declaration of a pointer is in C.It uses the * specification.
// Pointers are 32 bits or 4 bytes when compiling to an x86 system
// Pointers are 64 bits or 8 bytes when compiling to an x64 system
void readString(char* cPtr, char* cLength);
void printString(char* cPtr);
void test3();
void readNumbers(int* iPtr);
void printNumbers(int* iPtr, int iSize);
void test4();
void readStringGets(char* cPty, int iBufferSize);
void test5();
char* readStringReturnBuffer();

int main()
{
	// Create buffers to put data into
	char cArray2[10];
	char cArray[10];
	int iReturns;

	// Test 1 - use scanf to input a string
//	printf("Enter a string: ");
//	iReturns = scanf("%s", cArray); // scanf is dangerous; scanf_s provides guards
		// To use use scanf, #define _CRT_SECURE_NO_WARNINGS
		// or go to Properties | C/C++ | Preprocessor:
		// and add _CRT_SECURE_NO_WARNINGS to the Preprocessor Definitions
//	iReturns = scanf("%9s", cArray);
	// scanf %s should include the maximum size of the string as a modifier
	// This size should not include the null terminator

//	printf("%s\n", cArray);
//	printf("%d\n", iReturns);

//	printf("Enter another string: ");
	
//	iReturns = scanf_s("%9s", cArray, (unsigned int) sizeof(cArray));
	
//	printf("%s\n", cArray);
//	printf("%d\n", iReturns);

	// Let's do input from a separate function
//	readString(cArray, "6");
//	readString(cArray2, "9");
	// Let's do output from a seperate function
//	printString(cArray);
//	printString(cArray2);

	// Test 2 - scan f with multiple values
	// The format specifiers specifies two strings in this case
//	printf(" Enter two string separated by a space: ");
//	iReturns = scanf("%9s %9s", cArray, cArray2);

//	printString(cArray);
//	printString(cArray2);
//	printString("%d\n", iReturns);

	// Test 3 - 
//	test3();
	
	// Test 4 - use gets() to input a string
//	test4();
// 
	// Test 5 - returning an array (buffer) from the stack - not a good idea
	// TEST 5 WILL PROBABLY BE AN EXAM QUESTION
	test5();

	return EXIT_SUCCESS;
}

/*
* Purpose: Read in a string up to a given length
* Parameters: cPtr - pointer to an array of chars where the string will be stored
*			  cLengthPtr - pointer to a string containing the maximum length
* Returns: nothing
* Assumptions: cLengthPtr is a string of length 2 (including the null terminator)
* containing a digit for the length of the string to read in
*/
void readString(char* cPtr, char* cLengthPtr)
{
	// Create a format specifier
	char cFormat[4];
	// Initialize cFormat as an empty string
	cFormat[0] = '\0';

	// Use string concatenation to build up the format specifier
	// Cannot do this in C, string aren't object: cFormat = "%" + cLengthPtr + "s";
	strcat(cFormat, "%");
	strcat(cFormat, cLengthPtr);
	strcat(cFormat, "s");

	printf("Enter a string: ");
	// Note that scanf takes a format specifier (string) as a parameter,
	// and a pointer to a buffer (memory space) as the second parameter.
	// Note: That scanf quits reading after the first white space character in a string
	// Note that the "6" in cLengthPtr limits input to 6 characters not including the null terminator (safer).
	// Because we are passing in "6", this works out to scanf("%6s", cPtr);
	scanf(cFormat, cPtr);
}

void printString(char* cPtr)
{
	char someString[256] = "Some arbitrary string";

	printf("the result of reading in the string is :\n");
	printf("%s\n", cPtr);
}

// Test 3 - read in some integers
void test3()
{
	int iArray[5];
	int iSize;

	readNumbers(iArray); // should really ass in the size of the array
					     // readNumbers is poorly written here
	
	// How to calculate teh size of an array in C:
	// MUST be calculated in teh same scope where it is declared
	// If you need the size elsewhere, MUST pass it to whatever function you are using. 
	iSize = sizeof(iArray) / sizeof(int);
	printNumbers(iArray, iSize);
	
}

void readNumbers(int* iPtr)
{
	printf("Enter 5 numbers: ");
	// This function will actually read numbers until a non-number is entered
	// regardless of how many numbers are enterd - could write past buffer passed in
	
	// Note that scanf returns the number of reads that were successful
	// If it returns 0, no reads were successful
	// Recall that 0 is false in C.
	while (scanf("%d", iPtr))
	{
		// Move the pointer to the next inteer using pointer math
		// Note that + 1 means "Add one integer's worth of bytes",
		// so in this case, we add 4 to the address in iPtr
		iPtr += 1; // or iPtr = iPtr + 1; or iPtr++;
	}

}

void printNumbers(int* iPtr, int iSize)
{
	// The following line won't work. The size of a point is ALWAYS 4 bytes
	// on a n x86 system or 8 bytes on a x64 system
	// Size MUST be passed in 
//	iSize = sizeof(iPtr) / sizeof(int);

	printf("The numbers to be printed are: \n");
	for (int i = 0; i < iSize; i++)
	{
		// dereference iPtr to get the value at that address (pointed to)
//		printf("%d\n", *iPtr);
//		iPtr++;

		// or just use array notation
		printf("%d\n", iPtr[i]);
	}
}

// Test 4 - use gets() to input a string
void test4()
{
	char cArray[10];

	readStringGets(cArray, sizeof(cArray) / sizeof(char));
	printString(cArray);
}

void readStringGets(char* cPtr, int iBufferSize)
{
	int x; 
	int c; 

	printf("Enter an int: ");
	scanf("%d", &x); // must take address of x so that scanf can change x
	printf("You entered %d\n", x);
	// Must clear the input buffer after doing a scanf and before doing a gets_s
	// because scanf quits reading when it sees \n or any whitespace on the stdin (input buffer)
	// and leaves the newline or whitespace in stdin

//	getc(stdin); // Gets a charecter from the stream passed in to it
//	getchar(); // Gets a character from the stdin stream 

	// clear the buffer
	c = getchar();
	while (c != '\n')
	{
		c = getchar();
	}

	// Alternative formulation of reading a character until a newline is found:
	// Note the empty loop body - everything is being done in the while condition
//	while (getchar() != '\n'); this is just a shorted way of doing whats above.

	printf("Enter a big honking string: ");
//	gets(cPtr); // gets ("get string") is considered a dangerous function because it will read
				// past the end of the buffer passed to it
	gets_s(cPtr, iBufferSize); // will not read past bufferSize - invalid parameter handler
	// Another alternative is to use fgets(cPtr, iBufferSize, stdin);

}
// Test 5 - returning an an array (buffer) 
void test5()
{
	char* cPtr = NULL;
	cPtr = readStringReturnBuffer();
	printString(cPtr);
}

char* readStringReturnBuffer()
{
	// Memory is allocated on the stack - bad idea to return it
	// becuase stack frame is popped off when the function is done
	// Pass in the buffer instead OR dynamically allocate memory on the heap (malloc)
	char cBuffer[256];

	printf("Enter a big string: ");
	gets_s(cBuffer, sizeof(cBuffer) / sizeof(char));

	// We are returning teh address of memory on the stack!!!
	// This is a Bad IDea, because the stack frame will be ocerwriteen when 
	// some other function gets called. 
	return cBuffer;
}