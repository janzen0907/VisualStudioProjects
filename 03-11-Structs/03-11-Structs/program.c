#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

// Add these lines to enable memory leak detection
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


void testStructureBasicFormat()
{
	// Does this create a struct or a reference to a struct? A struct
	struct BirthDate bd1;

	// Try to add a value to a struct member.
	// It works. This struct is created on the stack.
	bd1.day = 17;

	// Note that the other attributes are not initialized - just set to random data
	DisplayBirthDateBasic(bd1);

	// Instantiate a struct with data
	struct BirthDate bd2 = { "Ada", 'f', 21, 3, 1987 };
	DisplayBirthDateBasic(bd2);

	// Access an attribute
	bd2.month = 4;

	// Alternatively, we can do it in a weird way
	*(&bd2.day + 2) = 1999; // not good practice, but shows we can manipulate memory
	DisplayBirthDateBasic(bd2);

	/*
	How big is a struct? Depends on the order the attributes are declared.
	By default, the attributes align on 4-byte boundaries (on this system).
	Therefore, an int will always align on a 4-byte boundary. The 5 bytes for cName
	will actually take up 8 bytes, even though only 5 are required. If gender is
	placed immediately after cName, it will fit in the remaining 3 bytes of cName.
	If added as the last attribute, gender will take up an entire 4-byte chunk.
	So with byte alignment set to anything other than 1, the order that you
	declare attributes can affect the size of the overall structure.
	In C, we can set the byte alignment for structs.
	*/
	printf("\n\nThe size of the struct is %zu\n", sizeof(bd1));
}


void testStructureDeclarationsWithTypedef()
{
	BirthDateTD bd = { "Mike", 'm', 31, 12, 1980 };

	// Can we do assignment?
	BirthDateTD bd1 = bd;

	// Modify bd1
	bd1.day = 1;

	// This shows that there are two separate structs created by assignment.
	DisplayBirthDateTypedef(bd);
	DisplayBirthDateTypedef(bd1);

	// Are structs pass by value or pass by reference?
	AlterBirthDate(bd1);
	DisplayBirthDateTypedef(bd1); // still displays 1980
	// This shows that the struct is pass by value (a copy of the struct was made)

	AlterBirthDateByRef(&bd1);
	DisplayBirthDateTypedef(bd1); // displays changed year
}


void testDynamicallyAllocatedStructs()
{
	BirthDateTD* bdPtr = NULL;

	// Try to access an attribute.
	// Crashes program - no memory allocated.
	//bdPtr->day = 12;

	bdPtr = (BirthDateTD*)malloc(sizeof(BirthDateTD));
	if (bdPtr != NULL)
	{
		// Set the day
		bdPtr->day = 13;

		// Set the name
		strcpy_s(bdPtr->cName, NAME_SIZE, "Mike");

		DisplayBirthDateTypedef(*bdPtr); 
			// Uninitialized variables are just whatever was on heap

		// If we do declare a dynamically allocated struct, we must free it.
		// Make sure that you free any dynamically allocated attributes first, if any.
		free(bdPtr);
		bdPtr = NULL;
	}
}


void testStudentStruct()
{
	int marks[] = { 89, 93, 96, 100 };

	student* sPtr = CreateStudent("Mike Grzesina", 123456789,
		marks, sizeof(marks) / sizeof(int));

	DisplayStudent(*sPtr);

	FreeStudent(sPtr);
	sPtr = NULL;
}


void testClassroom()
{
	classroom c = PopulateClassroom();
	DisplayClassroom(c);

	FreeClassroom(&c);
}


testFertilizerUnion()
{
	FertilizerQuantity fq;

	// How big is the union in bytes?
	printf("The size of the union is %zu\n", sizeof(fq)); // 8 bytes - largest is double

	// Assign a value to truckloads
	fq.truckloads = 3;

	// Assign a value to bags
	fq.bags = 400;

	// Assign a value to tons
	fq.tons = 12345.6789;

	printf("The value of truckloads is: %d\n", fq.truckloads);
	printf("The value of bags is: %u\n", fq.bags);
	printf("The value of tons is: %f\n", fq.tons);

	printf("The address of truckloads is: %p\n", &fq.truckloads);
	printf("The address of bags is:       %p\n", &fq.bags);
	printf("The address of tons is:       %p\n", &fq.tons);
}


void testColorConversion()
{
	colorVal c;
	c.val = 0x2A3BFF1C;
	c.components.a = 0xFF;

	printf("The size of colorVal: %zu\n", sizeof(colorVal)); // 4 bytes
	printf("The whole int is %x\n", c.val);
	printf("The Red component is %x\n", c.components.r);
	printf("The Green component is %x\n", c.components.g);
	printf("The Blue component is %x\n", c.components.b);
	printf("The alpha channel (transparency) is %x\n", c.components.a);
}




int main()
{
	printf("Size of struct BirthDate is: %zu\n", sizeof(struct BirthDate));
	printf("Size of BirthDateTD is: %zu\n", sizeof(BirthDateTD));
	printf("Size of student is: %zu\n", sizeof(student));
	printf("Size of classroom is: %zu\n", sizeof(classroom));
	printf("Size of pixel32 is: %zu\n\n", sizeof(pixel32));
	printf("Size of Computer is: %zu\n\n", sizeof(Computer));
	printf("Size of MemorySize union is: %zu\n\n", sizeof(MemorySize));

	//testStructureBasicFormat();
	//testStructureDeclarationsWithTypedef();
	//testDynamicallyAllocatedStructs();

	//testStudentStruct();

	// Test GetStudent() function
	//student* sPtr = GetStudent();
	//DisplayStudent(*sPtr);
	//FreeStudent(sPtr);

	//testClassroom();

	//testFertilizerUnion();
	testColorConversion();

	// Add the following to detect memory leaks
	// WHEN YOU ARE RUNNING IN DEBUG MODE
	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
}
