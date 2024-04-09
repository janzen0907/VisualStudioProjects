#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // for malloc
#include <string.h> // for strlen, strcpy
#include "structs.h"

void DisplayBirthDateBasic(struct BirthDate bd)
{
	printf("\nName is %s\n", bd.cName);
	printf("Gender is %c\n", bd.cGender);
	printf("Date is %d %d %d\n", bd.day, bd.month, bd.year);
}


void DisplayBirthDateTypedef(BirthDateTD bd)
{
	printf("\nName is %s\n", bd.cName);
	printf("Gender is %c\n", bd.cGender);
	printf("Date is %d %d %d\n", bd.day, bd.month, bd.year);
}


void AlterBirthDate(BirthDateTD bd)
{
	printf("\nSize of passed in BirthDateTD is %zu\n", sizeof(bd)); // size 18
	bd.year = 2001;
	DisplayBirthDateTypedef(bd); // will display 2001 but not change calling struct
}


void AlterBirthDateByRef(BirthDateTD* bdPtr)
{
	printf("\nSize of passed in bdPtr: %zu\n", sizeof(bdPtr)); // size 8 (x64) or 4 (x86)
	//(*bdPtr).year = 2023;
	bdPtr->year = 2022;
}


// A function that creates a student and initializes the attributes.
// This is similar to the keyword new in C# or Java. It allocates the instance
// AND it is also like a constructor that sets all the attributes.
student* CreateStudent(char* cNamePtr, int iStudentNum, int* iMarksPtr, int iMarkCount)
{
	// Allocate memory on the heap
	student* sPtr = (student*)malloc(sizeof(student));

	if (sPtr != NULL)
	{
		// Allocate room for the name
		sPtr->cNamePtr = (char*)malloc((strlen(cNamePtr) + 1) * sizeof(char));
		strcpy(sPtr->cNamePtr, cNamePtr); // like this.cNamePtr = cNamePtr;

		// Assign student number
		sPtr->iStudentNum = iStudentNum; // like this.iStudentNum = iStudentNum

		// Marks array
		sPtr->iMarksPtr = (int*)malloc(iMarkCount * sizeof(int));
		memcpy(sPtr->iMarksPtr, iMarksPtr, iMarkCount * sizeof(int));

		// Set the number of marks
		sPtr->iMarksCount = iMarkCount;
	}

	return sPtr;
}


// A function to display the data stored in a student instance.
// Takes a student instance, not a pointer. Sometimes this is done as a copy
// of the student is made. If this function messes up the struct somehow, it
// will not mess up the struct passed in.
void DisplayStudent(student s)
{
	printf("\nName: %s\n", s.cNamePtr);
	printf("Student number: %d\n", s.iStudentNum);
	printf("Marks: ");
	for (int i = 0; i < s.iMarksCount; i++)
	{
		printf("%d ", s.iMarksPtr[i]);
	}
	printf("\n");
}


// This function will free the memory allocated for a student instance.
// In C++, there is a function called a destructor where the programmer is
// supposed to release memory and clean up any other resources - this is similar.
void FreeStudent(student* sPtr)
{
	// Free the dynamically allocated name and marks array
	free(sPtr->cNamePtr);
	sPtr->cNamePtr = NULL;

	free(sPtr->iMarksPtr);
	sPtr->iMarksPtr = NULL;

	// Do we free the struct itself? Only if the struct is dynamically allocated.
	// This is a design decision.
	free(sPtr);
	sPtr = NULL;
}


// Get student data from the user
student* GetStudent()
{
	char cName[MAX_NAME_SIZE];
	int iMarks[2];
	int iStudentNum;

	// Get the name
	printf("Enter the student name: ");
	gets_s(cName, MAX_NAME_SIZE);

	// Get the student number
	printf("Enter the student number: ");
	scanf("%d", &iStudentNum);

	// Get two marks
	printf("Enter two marks, separated by a space: ");
	scanf("%d %d", iMarks, iMarks + 1);
	getc(stdin); // Clear any newline characters for next time

	return CreateStudent(cName, iStudentNum, iMarks, 2);
}


// Ask the user to populate the classroom. First ask how many students.
// Then ask for data for each student.
classroom PopulateClassroom()
{
	// Create an instance of the classroom on the stack
	classroom c;

	printf("How many students are in the classroom? ");
	scanf("%hu", &c.sNumStudents);
	getc(stdin);

	// Need to allocate space for the array of student pointers
	c.sPtrPtr = (student**)malloc(c.sNumStudents * sizeof(student*));

	for (int i = 0; i < c.sNumStudents; i++)
	{
		c.sPtrPtr[i] = GetStudent();
	}

	return c;
}


// Display each student in the classroom
void DisplayClassroom(classroom c)
{
	printf("\nDisplaying the classroom:\n");
	for (int i = 0; i < c.sNumStudents; i++)
	{
		DisplayStudent(*(c.sPtrPtr[i])); // or *c.sPtrPtr[i] since . has precedence
	}
}

// Free memory associated with classroom
void FreeClassroom(classroom* classPtr)
{
	// Free students
	for (int i = 0; i < classPtr->sNumStudents; i++)
	{
		FreeStudent(classPtr->sPtrPtr[i]);
		classPtr->sPtrPtr[i] = NULL;
	}

	// Free classroom
	free(classPtr->sPtrPtr);
	classPtr->sPtrPtr = NULL;

	// We could also free the classroom - this is a design decision
	// In this case, we used classroom structs, not a dynamically allocated classroom
	// so it would not be appropriate to free the classroom.
}
