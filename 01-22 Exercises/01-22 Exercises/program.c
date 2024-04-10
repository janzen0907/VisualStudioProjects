#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#define FNAME_BUFFER 20
#define LNAME_BUFFER 20
enum BOOL {false, true};



void enter_name(char* cNamePtr, char* cPrompt)
{
	// NOT WORKING OR COMPLETE
	// Use scanf to enter a name
	printf("Please enter your name: ");
	scanf_s("%s", cNamePtr ,FNAME_BUFFER);

	printf("Your name is : %s\t %s\n", FNAME_BUFFER, LNAME_BUFFER);
	
	
}

void test_enter_name()
{
	// NOT COMPLETE
	enter_name(FNAME_BUFFER, LNAME_BUFFER);
}

void string_funcs()
{
	char string[255] = "This is a string";
	char copiedString[255];
	char part1[255] = "This is";
	char part2[255] = " a string";
	int result;
	int sameResult;
	char concatString[255];


	char* stringPtr = &string;

	printf("The length of the string is %d\n", strlen(string));
	
	// Example of using strcpy_s
	// First is where you want to copy too, then a count of the orignal and the original
	strcpy_s(copiedString, _countof(string), string);
	printf("Using strcpy the string is %s\n", copiedString);

	// Left off here
	strcat_s(*concatString , _countof(part2), part2);
	printf("Using a concatenated strin %s\n", concatString);

	//result = strcmp(string, part1);
	//printf("String compared to part 1 = %d\n", result);

	//result = strcmp(string, string);
	//printf("These string should be the same = %d\n", sameResult);
}



void enumerations()
{
	int i = 1;
	// Instance of enumeration
	enum BOOL done = false;
	do
	{
		printf("%d\n", i);
		i++;
		if (i > 15)
		{
			done = true;
		}
	} while (!done);
}

void main()
{
	//enumerations();
	//test_enter_name();
	string_funcs();
}