#include <stdio.h>
#include "functions.h"
#include <string.h>


extern int globalCount; // says that hloabl variable already exists externally (in another file)

void modify_my_array(unsigned short int* sArrayPtr, int iArraySize)
{

	char* cPtr = NULL;
	unsigned int* iPtr = NULL;

	for (int i = 0; i < iArraySize; i++)
	{
		(*sArrayPtr)--; // subtract one from each array element
		sArrayPtr++; // move to the next element
	}
	// sArrayPtr now contains the address AFTER the last position in the array
	// How do we get back to the start of the array?
	sArrayPtr -= iArraySize;

	cPtr = (char*)sArrayPtr;
	*cPtr = 0x55; // or 'U';

	*(cPtr + 3) = 0; // same as cPtr[3]

	iPtr = (unsigned int*)sArrayPtr;
	iPtr += 2;
	*iPtr = 0x56555453;


	printf("sArrayPtr:\t%p\n", sArrayPtr);
	printf("cPtr:\t\t%p\n", cPtr);
	printf("iPtr:\t\t%p\n", iPtr);
	printf("%x\n", *(sArrayPtr + 2));
	printf("%p\n", sArrayPtr + 2); 
	printf("%x\n", *iPtr);
	printf("%p\n", &iPtr);

	// Exam Q: Given a list of values and a list of addresses, what points to what?

}

int getGradeGlobal()
{
	int grade;

	printf("Enter a grade: ");
	scanf_s("%d", &grade);
	while (grade < 0 || grade > 100)
	{
		printf("Invalid grade. Must be between 0 and 100.\n");
		printf("Enter a grade: ");
		scanf_s("%d", &grade);
	}
	globalCount++;

	return grade;
}

int getGradeLocal()
{
	int grade;
	static int count = 0; // declared in the BSS memory area instead of on the stack frame

	printf("Enter a grade: ");
	scanf_s("%d", &grade);
	while (grade < 0 || grade > 100)
	{
		printf("Invalid grade. Must be between 0 and 100.\n");
		printf("Enter a grade: ");
		scanf_s("%d", &grade);
	}
	count++;
	printf("Local grade count: %d\n", count);

	return grade;
}
//Broken
int getGradePassByRef(int* iCountPtr)
{
	int grade;

	printf("Enter a grade: ");
	scanf_s("%d", &grade);
	while (grade < 0 || grade > 100)
	{
		printf("Invalid grade. Must be between 0 and 100.\n");
		printf("Enter a grade: ");
		scanf_s("%d", &grade);
	}
	(*iCountPtr)++;
	printf("Local grade count: %d\n", *iCountPtr);

	return grade;
}


void writeData(FILE* filePtr)
{
	int id;
	char cNameBuffer[MAX_NAME_SIZE];
	unsigned char nameLength; // anything less than 256 or not negative can be unsigned


	printf("Enter an id number (0 to quit): ");
	scanf_s("%d", &id);
	getchar(); // get the newline character off stdin
	
	while (id != 0)
	{
		printf("Enter a name: ");
		gets_s(cNameBuffer, MAX_NAME_SIZE);
		
		// Write to a binary file
		fwrite((void*) & id, sizeof(int), 1, filePtr);
		// This will now write variable name records, rather than fixed length records
		nameLength = (unsigned char)strlen(cNameBuffer);
		fwrite((void*)&nameLength, sizeof(unsigned char), 1, filePtr);
		fwrite((void*)cNameBuffer, sizeof(char) * (nameLength + 1), 1 , filePtr);
		// fwrite((void*)cNameBuffer, sizeof(char) * MAX_NAME_SIZE, 1, filePtr);
		// Should check for successful writing. This is an excercise.

		printf("Enter an id number (0 to quit): ");
		scanf_s("%d", &id);
		getchar(); // get the newline character off stdin
	}
}
// Read data from the file passed in AND look for a specific id
void readData(FILE* filePtr)
{
	int id, iNumberToFind;
	char cNameBuffer[MAX_NAME_SIZE];
	unsigned char nameLength;
	do
	{

		printf("Enter an id number to find (0 to quit): ");
		scanf_s("%d", &iNumberToFind);

		// could have gotten number of records. Then use a for loop based off the amount of records
		//feof checks to see if we are at the end of the file or not
		// Checks if the last read went past the end of the file
		fread((void*)&id, sizeof(int), 1, filePtr);
		while (!feof(filePtr)) // keep reading until the end of the file
		{
			printf("ID %d read in - %s\n", id, id == iNumberToFind ? "Found" : "not found");
			//fread((void*)cNameBuffer, sizeof(char) * MAX_NAME_SIZE, 1, filePtr);
			// Still need the name length so we know how far to go
			fread((void*)&nameLength, sizeof(unsigned char), 1, filePtr); // save name length in the file
			//fread((void*)cNameBuffer, sizeof(char) * (nameLength + 1), 1, filePtr);
			// printf("Name %s read in \n", cNameBuffer);
			fseek(filePtr, nameLength + 1, SEEK_CUR); // Skip over the name from the current location
			// This was the first line orignally. Have to move it to after for program to work as expected
			fread((void*)&id, sizeof(int), 1, filePtr);
		}
		fseek(filePtr, 0, SEEK_SET); // After we read through the file go back to the start
	} while (iNumberToFind != 0);
}