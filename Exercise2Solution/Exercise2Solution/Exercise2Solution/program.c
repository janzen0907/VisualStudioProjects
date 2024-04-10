/*
	Filename:	program.c
	Author:		Sample Solution
	Course:		COSC 292 (Advanced Programming 2)
	Instructor:	Michael Grzesina
	Date:		Winter 2024
	Purpose:	Main file for practice using pointers and arrays in C
*/

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"


/*
	Function:		testSwap
	Purpose:		Test the swap function by swapping values of two integers
	Parameters:		none
	Returns:		nothing
	Assumptions:	none
*/
void testSwap()
{
	int x = 10;
	int y = 20;

	// You must figure out how to call the function correctly!
	// It needs the addresses of x and y so that we can change the values of the integers in this function.
	// swap(x, y) would just pass a copy of the values of x and y to the function.
	swap(&x, &y);

	// Should print out x: 20, y: 10
	printf("x: %d, y: %d\n", x, y);
}


/*
	Function:		testInteger
	Purpose:		Test the newInteger function
	Parameters:		none
	Returns:		nothing
	Assumptions:	none
*/
void testInteger()
{
	// Syntax wise, this is allowed.
	// Only a warning when compiling functions.c - "returning address of local variable or temporary: i".
	// Not safe - memory address will eventually be overwritten by another stack frame's values.
	// No, should not return the address of anything declared on the stack in a frame that is about to be popped off the stack.

	int* iPtr = newInteger();
//	printf("Hello Cruel World\n"); // Try it without commenting out this line and see what happens
	printf("The integer is %d\n", *iPtr);
}


/*
	Function:		testHideUnhide
	Purpose:		Test the hideString and unHideString functions
	Parameters:		none
	Returns:		nothing
	Assumptions:	none
*/
void testHideUnhide()
{
	int iArray[] = { 32842938,9329823,8439339, 7943085 };
	int iArraySize = sizeof(iArray) / sizeof(int);
	char cArray[] = "Bill";

	printf("iArray is originally: ");
	for (int i = 0; i < iArraySize; i++)
	{
		printf("%d ", iArray[i]); // or try %x to see the hex values of the bytes
	}
	printf("\n");

	hideString(iArray, cArray);
	//You may want to print out iArray next with a for loop
	//to see how the int values have changed.
	printf("iArray is changed to: ");
	for (int i = 0; i < iArraySize; i++)
	{
		printf("%d ", iArray[i]); // or try %x to see only the 3rd byte has changed
	}
	printf("\n");

	//This should print out “Bill”
	unHideString(iArray);
}


/*
	Function:		main
	Purpose:		Starting point for code running various test functions
	Parameters:		none
	Returns:		status of program when program exits
	Assumptions:	none
*/
int main()
{
	testSwap();
	testInteger();
	testHideUnhide();

	return EXIT_SUCCESS;
}
