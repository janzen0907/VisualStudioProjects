#include <stdio.h>
#include "memory.h"

int memoryMap(float x)
{
	static int i = 0; //BSS segment
	int a = 1235257896;
	double d = 9.0;
	int* iPtr = &a; // pointer to an int, point to a (containing the addres of a)
	float b = 3.2f;
	char c = 'a';
	short s = 10815;
	char cArray[] = "Hello";

	//Print the address of each variable 
	//The "Address of" operator is the overloaded &
	//Note: That %p is used for printing addresses in hexadecimal
	printf("The address of int i is \t%p\n", &i);
	printf("The address of int a is \t%p\n", &a);
	printf("The value of int a in hex is \t%x\n", a); //print in hex using %p
	printf("The value of a as a char is \t%c\n\n", a); //print in hex using %p
	
	printf("The address of double d is \t%p\n", &d);
	printf("The address of float b is \t%p\n", &b);
	printf("The address of pointer iPtr is \t%p\n", &iPtr);
	printf("The value stored in iPtr is \t%p\n", iPtr);
	printf("The address of char c is \t%p\n", &c);
	printf("The value of char c in hex is \t%x\n\n", c);

	printf("The address of short s is \t%p\n", &s);
	printf("The value of short s in hex is \t%x\n\n", s);

	//Note that the name of an array is its address. & is not required
	printf("The address of char cArry is \t%p\n", cArray);
	printf("The address of char cArry is \t%p\n", &cArray); //&will still work

	printf("The value of the argument is %f\n", x);
	//Address of the parameter
	printf("The address of float x is \t%p\n", &x);

	//Print the address of the function itself
	//Note that the name of the function stores its address
	printf("The address of memoryMap is \t%p\n", memoryMap);

	//Recursive call to demonstrate that every value is stored in a different location each time
	// recursion occurs. The only things that stays the same is the address of memoryMap and int i as its static
	//memoryMap(x + 1.0f); //used to demonstrate stack overflow. 

	return 0;
}