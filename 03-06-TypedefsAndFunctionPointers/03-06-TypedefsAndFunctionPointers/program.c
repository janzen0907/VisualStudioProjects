#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"


void testTypedefs()
{
	Length x = 3;
	Length y = 5;
	printf("x plus y = %d\n", x + y);

	String p;
	p = "Hello world";
	printf("The string is %s\n", p);
	printf("The first character is %c\n", *p);

	UShort s = 60000;
	printf("The value of s is %hu\n", s);
}


int doSquare(int x)
{
	return x * x;
}


int doAdd(int x)
{
	return x + x;
}


int doNothing(int someNumber)
{
	return someNumber;
}


// Do we need to match the signature of the function pointer?
// No, it will still compile and run (but may produce unpredictable results).
// You need to make sure that there are no conversion errors from one type to the next.
// In general, using functions that do not have matching signatures is not a good idea.
int dontMatchSignature(short x)
{
	return (int)x;
}


int compareToAscending(int first, int second)
{
	return first - second;
}


int compareToDescending(int a, int b)
{
	return b - a;
}


int compareLastDigit(int a, int b)
{
	int firstLastDigit = a % 10;
	int secondLastDigit = b % 10;

	return firstLastDigit - secondLastDigit;
}


int main()
{
	int iArray[] = { 45, 56, 626262, 30, 2 };
	size_t iSize = sizeof(iArray) / sizeof(int);
		// size_t is set with typedef in <stdio.h> and <stdlib.h>
		// and has different settings (unsigned int vs. unsigned long long)
		// for different environments (x86 vs. x64).

	//testTypedefs();

	// Note that we pass a function into iterateNumbers as the last parameter.
	// The name of the function stores its address so we don't need &.
	iterateNumbers(iArray, iSize, doSquare);
	iterateNumbers(iArray, iSize, doAdd);
	iterateNumbers(iArray, iSize, doNothing);
	iterateNumbers(iArray, iSize, dontMatchSignature);

	// sortInts(iArray, iSize, compareToAscending);
	// sortInts(iArray, iSize, compareToDescending);
	sortInts(iArray, iSize, compareLastDigit);
	for (int i = 0; i < iSize; i++)
	{
		printf("%d ", iArray[i]);
	}
	printf("\n");

	return EXIT_SUCCESS;
}
