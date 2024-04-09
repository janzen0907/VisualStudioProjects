#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Comments can be written as multi-line comments between slash-star and star-slash
* Only form of comments in the original C */
//Later versions of C allow single-line comments //

// #include is a pre-processor directive
//The pre-processor reads the source file looking for directives (starting with #) 
//In this case # include tells the pre-processor to find stdio.h
//and substitutes its text into this file

//#include is similar to "Using" statements in C# or "import" in Java
//Tells the pre-processor that there is some existing code that we want to use
//Note that <> tells the pre-processor to look in the built-in standard libraries
//We will use "" instead of <> to look in the local project first

//Another type of pre-proccesor directive is the define statement (note: no semicolon)
#define PI 3.14159f //This is a substitution, if you see PI substitue it for 3.14159

void primitaveTypes()
{
	char c = 'A'; //charecter literals are in single quotes
	int x = 4276803;
	float f = PI;
	double d = 12345.6579;

	//Print te value of the variables using format specifies that start with %
	//Google "Microsoft printf format specifies" to get information
	//https://learn.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions?view=msvc-170

	printf("The value of c is %c\n", c);
	printf("The value of c as an int is %d\n", c); //This will print the charecters ASCII value; 65
	printf("The value of x is %d\n", x);
	printf("The value of x in hex is %x\n", x);
	printf("The value of x as a charecter is %c\n", x);
	//Can us the format specifer to modify output
	//For instance, to display 10 charecter with 2 decimals
	printf("The value of d is %10.2f\n", d);

	//What are the sizes of each data type on our system? (may vary with system)
	//The sizeof operator is used to return the sizeof a data type, struct, array, etc.
	//Measured in bytes
	printf("The size of a char is %zu\n", sizeof(c)); //Size of returns a size type not an integer
	printf("The size of a int is %zu\n", sizeof(x));
	printf("The size of a float is %zu\n", sizeof(float));
	printf("The size of a double is %zu\n", sizeof(double));

}

void modifiers()
{
	//Note that C defaults to signed values (can be + or -)
	//Except for char, which is system dependent
	unsigned char e = 255; //unsigned char can store values from 0 to 255
	signed char c = 127;//signed char can store values from -128 to 127

	//"short" and "long"
	short int x; //will be 2 bytes on this platform
	short y; //Short form of writing a short int
	long int z; //no effect on this platform
	//Note that the only guarantees are that short <= int <= long
	//and that short must be at least 16 bits and long must be at least 32 bits

	long float f; //doubles the size to 8 bytes (same as double)
	long double d; //no effect on this platform (same as double)
	
	long long int ll; //newer versions of C allow long long as a modifier to int
		//guarenteed to be at least 64 bits

	//Add 1 to e and c
	e = e + 1;
	c += 1;

	printf("The value of e it %d\n", e);
	printf("The value of c it %d\n", c);

	printf("Size of short: %zu %zu\n", sizeof(x), sizeof(y));
	printf("Size of long: %zu\n", sizeof(z));
	printf("Size of long float: %zu\n", sizeof(f));
	printf("Size of long double: %zu\n", sizeof(d));
	printf("Size of long long: %zu\n", sizeof(ll));

}

void castDemo()
{
	int x;
	float y = 3.2f;
	float fahr = 115; //cast to a float
	float celc; //Note that unititialize values may have a random number

	//Assign y to x
	x = (int)y; //explicitly cast
	//Note x = y would work in C as it will cast it automatically unlike java.
	printf("The value of x is %d\n", x);
	
	printf("The temperature in Fahrenheit is %f\n", fahr);
	celc = ((float)5 / 9) * (fahr - 32); //cast 5/9 to avoid integer division
	printf("The temperature in Celcius is %f\n", celc);


}

void demoConstants()
{
	//Constants have the keyword cosnt
	const float pi = 3.14159f;
	//NOTE: Cannot be used on the left side on the expression operator. Cannot change the value
	//pi = pi + 1; 
	printf("The value of pi is %f\n", pi);
}

// Strings in C --> WAIT! There are no string objects in C.
void stringDemo()
{
	char myChar = 'm'; //single quotes for a charecter literal
	char s1[] = "William"; //can initialize a string literal to a char[]
	char s2[5];
	//s2 = "Jean"; //can't do assignment 
	s2[0] = 'J'; //arrays start at 0 and are referenced with []
	s2[1] = 'e';
	s2[2] = 'a';
	s2[3] = 'n';
	//You MUST remember to null terminate your strings
	s2[4] = '\0';

	printf("The value of myChar is %c\n", myChar);
	printf("The value of s1 is %s\n", s1);
	//can use sizeof on an array defined in the current function
	printf("The size of s1 is %zu\n", sizeof(s1)); //includes \0, null terminator
		//NOTE: William is 7 long but because of \0 its actually 8 long
	printf("The value of s2 is %s\n", s2);
	printf("The size of s2 is %zu\n", sizeof(s2));

}

void booleanDemo()
{
	int a = 3;
	_Bool b; //in newer versions of C, there is a _Bool data type
	bool b2 = false; // "bool" type is defined in the <stdbool.h> 


	//False returns 0 true returns 1 
	printf("%d\n", (a > 3)); //boolean values are integers - 0 for falsh
	printf("%d\n", (a <= 3)); // 1 for true
	
	//You can just use integer for boolean values
	if (a) //any non-zero integer is true 
	{
		printf("True\n");
	}

	b = (a < 3); //will print out as 0 (false)
	b = 3; //will print out as 1 (true)
	b = true; // no "true" keyword in C, but can add with $include <stdbool.h>
	//same with "false"
	printf("b is: %d\n", b);
	printf("b2 is: %d\n", b2);

	printf("Size of b is %zu\n", sizeof(b));
	printf("Size of b is %zu\n", sizeof(b2));

}

void pointerDemo()
{
	//Pointer stores a memory address
	char cArray[] = "This is a char array with a null terminator";
	char* cPtr = cArray; //A pointer to a char, set to the address of cArray
	int* iPtr = NULL; //A pointer to an int, set to NULL
	int iValue = 42424242;

	printf("Sizre of cArray: \t%zu\n", sizeof(cArray));
	printf("Size of cPtr: \t%zu\n", sizeof(cPtr));
	printf("Size of iPtr: \t%zu\n", sizeof(iPtr));
	//Size of a pointer is the same regardless of what it points at,
	//since it contains a memory address. The size will vary depedning on your system (x86 or x64) since they
	//have different address sizes. 

	//Use %p to print out the value of a pointer in hex
	printf("Value of cArray: \t%p\n", cArray);
	//This works because cArray is the address of the start of the array
	printf("Value of cPtr: \t%p\n", cPtr);
	printf("Value of iPtr: \t%p\n", iPtr);

	//Can get the address of an item and set a pointer to it using the 
	//address of & operator
	iPtr = &iValue;
	printf("New Value of iPtr: \t%p\n", iPtr);

	//Can dereference a pointer to get at the value it is pointing at
	//using the dereference operator *
	//%c = char, %d = digit, %x =  hex
	printf("cPtr dereferences as %c or %d or %x\n", *cPtr, *cPtr, *cPtr);
	printf("iPtr dereferences as %d or %x\n", *iPtr, *iPtr);

	//Pointer math - we can add values to pointers, but it adds the size of the 
	//data type being pointed at
	iPtr = (int*) cPtr; //assign the address in cPtr to iPtr, treat it as int*
	printf("New new Value of iPtr: \t%p\n", iPtr);
	printf("cPtr + 2 is: \t%p\n", cPtr + 2);
	printf("iPtr + 2 is: \t%p\n", iPtr + 2);
	//To change the value of a pointer, use += or ++ (like other variables)
	cPtr++;
	printf("New Value of cPtr: \t%p\n", cPtr);
	printf("Current value of *cPtr: \t%c\n", *cPtr);

}

void countLengthDemo()
{
	char cArray[] = "This is a message";
	char* cPtr = &cArray; //a pointer to a char, set to the address of the cArray
	int iLength;

	printf("The size of cArray is \t%zu\n", sizeof(cArray));
	printf("The size of cPtr is \t%zu\n", sizeof(cPtr));
	printf("The value of cPtr is \t%p\n", cPtr);

	iLength = 0;
	while (cArray[iLength] != '\0') //could also use (cArray[iLength] != 0) would be the same.
	{
		iLength++;
	}
	printf("The length of the string is \t%d\n", iLength);

	iLength = 0;
	while (cArray[iLength]) //null terminator is 0, and 0 is false
	{
		iLength++;
	}
	printf("The length of the string is \t%d\n", iLength);

	for (iLength = 0; *cPtr; iLength++) //Recall that *cPtr gives us the character
	{
		printf("The current value pointed to by cPtr is '%c'\n", *cPtr);
		printf("The value of cPtr is \t%p\n", cPtr);
		cPtr++; //"Walk" the pointer to the next character
	}
	printf("Walking the string gives \t%d\n", iLength);
	printf("The end value of cPtr is \t%p\n", cPtr);

	
}

//Program starts with a main function
int main(int argc, char* argv[])
{
	//Printf to output to the console
	printf("Hello");
	printf(" world\n"); //\n specifies a newline

	//primitaveTypes();
	//modifiers();
	//castDemo();
	//demoConstants();
	//stringDemo();
	//booleanDemo();
	//pointerDemo();
	countLengthDemo();

	return EXIT_SUCCESS;
}
