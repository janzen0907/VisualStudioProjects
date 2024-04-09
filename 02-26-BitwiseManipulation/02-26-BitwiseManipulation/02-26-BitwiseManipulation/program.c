#include <stdio.h>
#include <stdlib.h>

#define ANSWER_SIZE 5
#define ENGLISH_SIGNAL 0x01 //0000 0001
#define FRENCH_SIGNAL 0x02 //0000 0010
#define CREE_SIGNAL	0x04 // 0000 0100

/*
General Notes on Bit Operations
A bitwise operation operates on one or more bit patterns at the level of their 
individual bits. It is a fast, primitive action directly supported by the processor,
and is used to manipulate values for comparisons and calculations. On simple
low-cost processors, typically, bitwise operations are substantially faster for
division, several times faster for multiplication, and sometimes significantly faster
for addition. While modern processors perform addition and multiplication just as fast as
bit operations, bitwise operations do commonly use less power because of reduced
resources.
Source: https://en.wikipedia.org/wiki/Bitwise_operation
*/


// Print a value as a string of bits (up to 32 bits)
void showBits(int value, int bytes)
{
	unsigned int filter = 1;
	int bit;

	char* bitString = (char*)malloc(33);
	// Null terminator
	bitString[32] = '\0';

	for (bit = 0; bit < bytes * 8; bit++)
	{
		// Determine the value of the current bit
		if (value & filter)
		{
			bitString[31 - bit] = '1';
		}
		else
		{
			bitString[31 - bit] = '0';
		}
		filter *= 2; // Move to the next bit to the left
	}

	printf("The value %d in binary is \t%s\n", value, &bitString[32 - bytes * 8]);

	free(bitString);
	bitString = NULL;
}



// Bitwise AND & (not to be confused with logical AND &&)
// If both bits in the compared positions are 1, the bit in the resulting binary
// representation is 1; otherwise, the result is 0.
// Note: With a carefully constructed mask, we can preserve bits as they are or turn
// some bits off.
void bitAND()
{
	unsigned char a = 0x48;
	unsigned char b = 0xB8;
	unsigned char result = a & b;

	printf("Bitwise AND of a and b is %x\n", result);
	showBits(a, sizeof(char));
	showBits(b, sizeof(char));
	showBits(result, sizeof(char));

	int x = 0x030B1A0F;
	int maskFindBit = 0x00000004;
	int maskSetBitToZero = 0xFFFFFFFE;

	showBits(x, sizeof(int));
	showBits(x & maskFindBit, sizeof(int));
	showBits(x & maskSetBitToZero, sizeof(int));
}


// Bitwise OR | (not to be confused with logical OR ||)
// The result in each position is 1 if the first bit is 1 OR the second bit is 1 OR
// both bits are 1. Otherwise, the result is 0.
// Again, with a carefully constructed mask, we can preserve bits as they are or
// turn some bits on.
void bitOR()
{
	unsigned char a = 0x48;
	unsigned char b = 0xB8;
	unsigned char result = a | b;

	printf("Bitwise OR of a and b is %x\n", result);
	showBits(a, sizeof(char));
	showBits(b, sizeof(char));
	showBits(result, sizeof(char));

	int x = 0x030B1A0F;
	int mask = 0xFFFF0000; // set first 2 bytes to 1's and preserve the other bits

	showBits(x, sizeof(int));
	showBits(x | mask, sizeof(int));
}


// Bitwise exclusive OR aka XOR (^)
// The result in each position is 1 if only the first bit is 1 OR if only the second
// bit is 1, but will be 0 if both are 0 OR both are 1.
// Can be used to model the state of something like a two-way switch.
// Used in encryption C = plaintext^key, then P = ciphertext^key
// XOR with a full complement mask (FF) will flip the bits in the other operand.
// XOR with a mask of 0's will preserve the bits in the other operand.
void bitXOR()
{
	unsigned char a = 0x48;
	unsigned char b = 0xB8;
	unsigned char result = a ^ b;

	printf("Bitwise XOR of a and b is %x\n", result);
	showBits(a, sizeof(char));
	showBits(b, sizeof(char));
	showBits(result, sizeof(char));

	showBits(0xFF ^ b, sizeof(char));
	showBits(0x00 ^ b, sizeof(char));
}


// Bitwise NOT (~) is a unary operator that flips the bits
void bitInversion()
{
	unsigned char a = 0x48;
	unsigned char result = ~a;

	printf("Bitwise inversion of a is %x\n", result);
	showBits(a, sizeof(char));
	showBits(result, sizeof(char));
}


// Bitshift operators (>> and <<)
// No comparison is made, bits are simply moved left or right.
// Shifting right n positions is equivalent to dividing by 2 to the power n.
// Shifting left n positions is equivalent to multiplying by 2 to the power n.
void shiftOperators()
{
	short x = 37;
	int z = 1;
	signed char y = -128;
	char value = 0xD3;
	char mask = 0x0F;

	// Display x in binary
	printf("No shift in x\n");
	showBits(x, sizeof(short));

	// Note that bit shifting left is the same as multiplying by a power of 2
	printf("Shift x 1 bit to the left\n");
	showBits(x << 1, sizeof(short));

	// Note that bit shifting right is the same as dividing by a power of 2 (integer division)
	printf("Shift x 2 bits to the right\n");
	showBits(x >> 2, sizeof(short));

	printf("Shift z 30 bits to the left\n");
	showBits(z << 30, sizeof(int));

	printf("Shift z 31 bits to the left and then 1 bit back to the right\n");
	showBits(z << 31 >> 1, sizeof(int));
	// Note that the right shift of 1 resulted in padding = 1.
	// If the value is a signed value, the padding is determined by the value of the sign bit.
	// If the sign bit is set (to 1), then padding will be 1's, otherwise 0's.
	// This is why we often use unsigned values when doing bit operations.

	printf("y without shifting\n");
	showBits(y, sizeof(char));
	printf("Shift y left by 1\n");
	showBits((unsigned char)(y << 1), sizeof(char));
	printf("Shift y right by 1\n");
	showBits(y >> 1, sizeof(char));

	// Masking demo
	printf("value\n");
	showBits(value, sizeof(char));
	printf("mask\n");
	showBits(mask, sizeof(char));

	// The lower "nibble" of value
	printf("The lower nibble of value is\n");
	showBits(value & mask, sizeof(char));

	// The upper nibble of value
	printf("The upper nibble of value is\n");
	showBits((value >> 4) & mask, sizeof(char));
}


// Question 1:
// Write a function swapNibbles that will take an unsigned char and
// make the low order 4 bits into the high order 4 bits and also
// make the high order 4 bits into the low order 4 bits
// and return the result. So 11010011 would return 00111101.
unsigned char swapNibbles(unsigned char original)
{
	return original >> 4 | original << 4;
}


// Question 2:
// Write a function blendNibbles that will take two unsigned chars and
// return a result which contains the high order nibble of the first unsigned char
// and then (as the low order nibble of the result) the high order nibble of the
// second unsigned char. So 10001111 and 01101110 would return 10000110.
unsigned char blendNibbles(unsigned char first, unsigned char second)
{
	// or will maintain the none 0 bits
	return (first & 0xF0) | (second >> 4);
}

// Question 3:
// Write a function called reverseBits. Given an integer, return another integer where
// the bits are reversed. So, pass is 10001101 and return 10110001.
unsigned int reverseBits(unsigned int original)
{
	unsigned int reverse = 0; // start with all 0's only need to set 1's
	int numBits = sizeof(original) * 8;

	for (int i = 0; i < numBits; i++)
	{
		// check if the bit is set
		if (original & (1 << i))
		{
			reverse |= (1 << (numBits - 1 - i));
		}
	}


	return reverse;
}


// Question 4:
// Check out the precedence chart at
// https://en.cppreference.com/w/c/language/operator_precedence
// Write a function called testPrecedence. Write some test cases to test the
// precedence of various operators. For example, x | y << 1 (does | or << have precedence?).
void testPrecedence()
{
	unsigned char x = 1;
	unsigned char y = 1;

	printf("x | y is %x\n", (x | y));
	printf("x | y << is %x\n", (x | y << 1)); // result is 0000 0011
		// because << has precedence

	printf("x | y << is %x\n", ((x | y) << 1)); // result is 0000 0011
	// because we do x | y first in () parenthese

	x = 5; // 0000 0101
	y = 7; // 0000 0111
	unsigned char z = 3; //0000 0011
	printf("x ^ y | z is %x\n", x & y | z); //0000 0111
	printf("x & (y |z) is %x\n", x & (y | z)); //0000 0101

}

// Question 5a:
// Write a function that will ask the user for a y/n answer
// asking if they speak various languages
// e.g. Do you speak English (y/n)?
//      Do you speak French (y/n)?
//      Do you speak Plains Cree (y/n)?
// Have the function return a single unsigned char with bits set for each answer
// 1 for yes, 0 for no
unsigned char setLanguages()
{
	char answer[ANSWER_SIZE];
	unsigned char languages = 0; //assume no languages spoken
	
	// This example uses or | to set the signals

	printf("Do you speak English (Y|N)");
	gets_s(answer, ANSWER_SIZE);
	if (answer[0] == 'y')
	{
		languages = languages | ENGLISH_SIGNAL;
	}

	printf("Do you speak French (Y|N)");
	gets_s(answer, ANSWER_SIZE);
	if (answer[0] == 'y')
	{
		languages = languages | FRENCH_SIGNAL;
	}

	printf("Do you speak Cree(Y|N)");
	gets_s(answer, ANSWER_SIZE);
	if (answer[0] == 'y')
	{
		// Can do |= instead of the above
		languages |= CREE_SIGNAL;
	}
	
	return languages;
}

// Question 5b:
// Write a second function that will take in an unsigned char and will print
// greetings for each language that the unsigned char has bits set for
// e.g. Hello
//      Bonjour
//      Tan'si
void displayGreetings(unsigned char languages)
{
	if (languages & ENGLISH_SIGNAL)
	{
		printf("Hello!\n");
	}
	if (languages & FRENCH_SIGNAL)
	{
		printf("Bonjour!\n");
	}
	if (languages & CREE_SIGNAL)
	{
		printf("Tan'si!\n");
	}
}

// Question 6:
// When done, create a new project (or write functions within this project)
// that will ask for an input filename and an output filename,
// then read each byte from the input filename (use fgetc), combine that byte with
// a byte from the file "random.pad" (in the Exercises folder) using XOR, and write
// the combined byte to the output filename (use fputc).
// That will create an encrypted file (using random pad or one-time pad encryption)
// which can be decrypted by using the encrypted file as the input filename.
// https://en.wikipedia.org/wiki/One-time_pad
// Try it on message.ciphertext to decode the message that I created!


int main()
{
	//bitAND();
	//bitOR();
	//bitXOR();
	//bitInversion();
	//shiftOperators();
	unsigned char start = 0xAB;
	unsigned char end = swapNibbles(start);
	printf("We start with %x and end with %x\n", start, end);
	showBits(start, sizeof(char));
	showBits(end, sizeof(char));

	unsigned char first = 0xAC;
	unsigned char second = 0xDC;
	unsigned char result = blendNibbles(first, second);
	printf("The result is %x\n", result);
	showBits(result, sizeof(char));

	unsigned char languages = setLanguages();
	printf("%x\n", languages);
	displayGreetings(languages);

	unsigned int original = 0x0000057;
	unsigned int reversed = reverseBits(original);
	printf("We start with %x and end with %x\n", original, reversed);
	showBits(original, sizeof(int));



	return EXIT_SUCCESS;
}