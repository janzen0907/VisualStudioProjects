//Pre - Processor Directive
#include <stdio.h> // Add the standard input/output library
#include <stdlib.h> // Add the standard library

//Now we can create our C program. There is no classes, we are not working with OOP

//argc number of arguments passed into the program
//argv[] array of arguments
//Could also use void as we are not using these arguements
int main(int argc, char* argv[])
{
	long long int ll;
	long l; //Long is a modifier for int in C
	int i;
	short int s; //Short is a modifier for int
	char c;
	float f;
	double d;

	//Printf is a function in the standard IO library
	printf("Hello, world!\n");
	printf("Size of long long: %zu\n", sizeof(ll));
	//%D print as a decimal value, %zu got rid of the error
	printf("Size of long: %zu\n", sizeof(l));
	printf("Size of int: %zu\n", sizeof(i));
	printf("Size of short int: %zu\n", sizeof(s));
	//No byte data type so we use char to store bytes or charecters
	printf("Size of char: %zu\n", sizeof(c));
	printf("Size of float: %zu\n", sizeof(f));
	printf("Size of double: %zu\n", sizeof(d));
	//Returns the value 0 this is the int that the main will return 
	return EXIT_SUCCESS;
}