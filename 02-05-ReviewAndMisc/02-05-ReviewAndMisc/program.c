#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <errno.h>
#include <string.h>


int globalCount; // global variables are bad - try to avoid them

void enterGradesGlobal()
{
	int grade = getGradeGlobal();

	while (grade != 0)
	{
		printf("Grade is %d and status is %s\n", grade, grade >= PASSING_GRADE ? "PASS" : "FAIL:");
		printf("Grades enteres so far: %d\n", globalCount);
		grade = getGradeGlobal();
	}
	printf("Total grades entered: %d\n", globalCount);
}

void enterGradesLocal()
{

	int count = 0; //on the stack frame for enterGradesLocal
	int grade = getGradeLocal();

	while (grade != 0)
	{
		printf("Grade is %d and status is %s\n", grade, grade >= PASSING_GRADE ? "PASS" : "FAIL:");
		printf("Grades enteres so far: %d\n", count);
		grade = getGradeLocal();
	}
	printf("Total grades entered: %d\n", count);
}
/*
* Broken
* void enterGradesPassByRef()
{

	int count = 0; 
	int grade = getGradePassByRef(&count); // passing in the address of the local variable count

	while (grade != 0)
	{
		printf("Grade is %d and status is %s\n", grade, grade >= PASSING_GRADE ? "PASS" : "FAIL:");
		printf("Grades enteres so far: %d\n", count);
		grade = getGradePassByRef(&count);
	}
	printf("Total grades entered: %d\n", count);
}
*/


void writeRecords()
{
	FILE* filePtr = NULL;
	errno_t err = fopen_s(&filePtr, "data.dat", "wb");
	char messageBuffer[BUFFER_SIZE];

	if (err == 0)
	{
		writeData(filePtr);
		fclose(filePtr);
	}
	else
	{
		strerror_s(messageBuffer, BUFFER_SIZE, errno);
		printf("Error %d opening file: %s\n", errno, messageBuffer);
	}
}

void readRecords()
{
	FILE* filePtr = NULL;
	errno_t err = fopen_s(&filePtr, "data.dat", "rb");
	char messageBuffer[BUFFER_SIZE];

	if (err == 0)
	{
		readData(filePtr);
		fclose(filePtr);
	}
	else
	{
		strerror_s(messageBuffer, BUFFER_SIZE, errno);
		printf("Error %d opening file: %s\n ", errno, messageBuffer);
	}

}


int main(void)
{
	unsigned short int sArray[] = { 0xFFFF, 0x0000, 0xFEFE, 0x0101, 0x6261, 0x4344 };
	int arraySize = sizeof(sArray) / sizeof(unsigned short);

	//print the original array
	for (int i = 0; i < arraySize; i++)
	{
		printf("%4x/%5hu\t", *(sArray + i), *(sArray + i)); // or sArray[i]
		// sArray++; // is illegal - can't change the start of an array

	}
	printf("\n");
	
	// Need to pass in the size as well as the array
	modify_my_array(sArray, arraySize);

	for (int i = 0; i < arraySize; i++)
	{
		printf("%4x/%5hu\t", *(sArray + i), *(sArray + i)); // or sArray[i]
		// sArray++; // is illegal - can't change the start of an array

	}
	printf("\n");


	//enterGradesGlobal();
	//enterGradesLocal();
	//enterGradesPassByRef();
	//writeRecords();
	readRecords();

	return EXIT_SUCCESS;
}