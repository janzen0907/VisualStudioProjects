#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"

#define MAX_NAME_SIZE 30

void testOpenClose()
{
	// Name of text file, in read mode.
	int iErr = demoOpenClose("D:/foo.txt", "r");
	printf("The error number returned was %d\n", iErr);
}

void testRead()
{
	int iErr = demoRead("D:/foo.txt", "r");
	printf("The error number returned was %d\n", iErr);

}

void testWrite()
{
	int iErr = demoWrite("foobar.txt", "w", "abcefghi");
	printf("The error number was %d\n", iErr);
}

void testWriteBinary()
{
	int x = 123456789;
	int iErr = demoWriteBinary("foobar.bin", "wb", &x);
	printf("The number that was passed in (in hex) was %x\n", iErr);
}

void testInClassExWrite()
{

	exerciseBinaryWrite("testing.dat", "wb");
	
}

void testExerciseRead()
{
	int iSin = 0;

	printf("Enter the SIN# of the person to find: ");
	scanf("%d", &iSin);
	exerciseBinaryRead("exercise.dat", "rb", iSin);
}

int main()
{
	//testOpenClose();
	//testRead();
	//testWrite();
	//testWriteBinary();
	testInClassExWrite();
	// testExerciseRead();
	return EXIT_SUCCESS;
}