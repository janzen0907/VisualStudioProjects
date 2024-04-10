/*
	Filename:	program.c
	Author:		Sample Solution
	Course:		COSC 292 (Advanced Programming 2)
	Instructor:	Michael Grzesina
	Date:		Winter 2024
	Purpose:	Practice using enumerations and string functions in C
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MAX_NAME_SIZE	10

enum BOOL { false, true };


/*
	Function:		enumerations
	Purpose:		Sample code to explore how enumerations work
	Parameters:		none
	Returns:		nothing
	Assumptions:	the enum false is equal to 0 (and thus will be treated as false by C)
*/
// a. Study and run the following code. Define what an enum is.
//		An enum is a list of constants of type int. It declares a type for using these constants
//		and values for each constant (by default starting at 0 and increasing by 1).
void enumerations()
{
	int i = 1;
	//Instance of enumeration.
	enum BOOL done = false;

	do
	{
		printf("%d\n", i);
		i++;
		if (i > 15)
		{
			done = true;
		}
		// b. Try to print the values of the enum as a string and as an int. Is it possible?
//		printf("As a string, done is %s\n", done); // can't be done
		printf("As an int, done is %d\n", done);
	} while (!done);
}
// c. Is it possible to give enumerations a different starting value than 0?
//		Yes, during declaration of the enum. For instance, { false = 1, true = 2 } is allowed
//		(although the loop in the function above would no longer work - it is relying on false being 0).


/*
	Function:		enter_name
	Purpose:		Display a prompt and enter and store a string (without spaces)
	Parameters:		cNamePtr - the address of a string where a name will be stored
					cPrompt - the prompt to be displayed to the user asking for the string to be stored in cNamePtr
	Returns:		nothing
	Assumptions:	name will not exceed the size of the buffer pointed to by cNamePtr
*/
void enter_name(char* cNamePtr, char* cPrompt)
{
	printf(cPrompt);
	scanf("%s", cNamePtr); // or %9s, or build a specifier using MAX_NAME_SIZE - 1
}


/*
	Function:		test_enter_name
	Purpose:		Test the enter_name() function by asking for a first name and a last name
	Parameters:		none
	Returns:		nothing
	Assumptions:	enter_name will not enter a name greater than the buffer size (MAX_NAME_SIZE)
*/
void test_enter_name()
{
	char cFirstName[MAX_NAME_SIZE];
	char cLastName[MAX_NAME_SIZE];

	enter_name(cFirstName, "Enter a first name: ");
	enter_name(cLastName, "Enter a last name: ");

	printf("Your full name is %s %s.\n", cFirstName, cLastName);
}


/*
	Function:		string_funcs
	Purpose:		Try out various string functions
	Parameters:		none
	Returns:		nothing
	Assumptions:	none
*/
void string_funcs()
{
	char string1[] = "Hello world";
	char string2[] = "You are great";
	char string3[40]; // buffer for storing strings - could use #DEFINE for 40
	char string4[] = "Bob";

	// strlen
	printf("The length of string1 is %zu\n", strlen(string1));
	//Just for fun, overwrite the null terminator of string4
	//Bad idea to do this. strlen may return unpredictable results.
	string4[3] = '!';
	printf("The length of string4 is %zu\n", strlen(string4));

	// strcpy - parameters: first is destination, second is source
	// string3 is size 40 - unused space is still reserved, you are just not using it.
	// Note that the destination string's null terminator is copied over
	strcpy(string3, string1);
	printf("string3 = %s\n", string3);
	strcpy(string3, string2);
	printf("string3 = %s\n", string3);

	// strcat - concatenates the two strings. Overwrites the first parameter's null terminator.
	// Puts concatenated string into the first parameter.
	strcat(string3, " ");
	strcat(string3, string1);
	strcat(string3, " ");
	strcat(string3, string2);
	printf("string3 = %s\n", string3);

	// strcmp returns 0 if equal
	//Reassign string3 to an empty string (although strcpy will write over string3 anyway)
	string3[0] = '\0';
	strcpy(string3, string1); // try commenting out this line to see what happens; then comment out the line above as well

	if (strcmp(string3, string1) == 0)
	{
		printf("Equal\n");
	}
	else
	{
		printf("Not equal - strcmp equals: %d\n", strcmp(string3, string1));
	}
}


/*
	Function:		string_cat
	Purpose:		Take two strings and concatenate the second one onto the first one
	Parameters:		leftPtr - pointer to a buffer of characters containing a null-terminated string and extra space
					rightPtr - pointer to a null-terminated string
	Returns:		nothing
	Assumptions:	leftPtr points to a buffer that is big enough to contain the concatenated string
					Both leftPtr and rightPtr contain the address of null-terminated strings at the start
*/
void string_cat(char* leftPtr, char* rightPtr)
{
	int i = 0;
	// Create a pointer that points to the destination
	// Use pointer math to determine this position (or could walk pointer to correct location instead of using strlen)
	char* appendPtr = leftPtr + strlen(leftPtr);

	// Use a loop to copy characters over (could use strcpy).
	// Make sure your loop copies the null terminator.
	do
	{
		appendPtr[i] = rightPtr[i];
	} while (rightPtr[i++] != '\0'); // or while(rightPtr[i++]);
}


/*
	Function:		test_string_cat
	Purpose:		Test the string_cat method written above
	Parameters:		none
	Returns:		nothing
	Assumptions:	none
*/
void test_string_cat()
{
	char left[] = "Hello";
	char right[] = "World";
	char concat[20];

	concat[0] = '\0';

	string_cat(concat, left);
	string_cat(concat, " ");
	string_cat(concat, right);

	printf("%s\n", concat);
}


/*
	Function:		main
	Purpose:		Starting function for calling various test functions
	Parameters:		none
	Returns:		the status of the program when completed
	Assumptions:	none
*/
int main()
{
	enumerations();
	test_enter_name();
	string_funcs();
	test_string_cat();

	return EXIT_SUCCESS;
}
