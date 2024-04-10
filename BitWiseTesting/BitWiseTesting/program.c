#include <stdlib.h>
#include <stdio.h>
#include "encrpyt.h" 

/// <summary>
/// The following fucntion will take in a byte and mix them around as request
/// Given a byte: 10010011
// Swap as follows : 00101110
/// </summary>
/// <param name="byte"></param>
/// <returns>swappedBytes</returns>
unsigned char mixBits(unsigned char byte)
{

    // Extract the first two bits and shift them to the right by 6
    unsigned char firstTwoBits = (byte & 0xC0) >> 6;

    // Get the last 3 bits and shift them over by 2
    unsigned char lastFewBits = (byte & 0x07) << 2;

    // Get bits 4 and 5, shift them to the left by 2
    unsigned char bitsFourAndFive = (byte & 0x30) << 2; 
    // Move the bit in position 2 to position 3 
    unsigned char newBitTwo = (bitsFourAndFive & 0x40) >> 1;
    // Move the bit in position 3 to position 2
    unsigned char newBitThree = (bitsFourAndFive & 0x20) << 1;
    
    // Rebuild the bytes by combining the individual elements
    unsigned char swappedByte = firstTwoBits | newBitTwo | newBitThree | lastFewBits;
    
    // return the bytes swapped
    return swappedByte;
}
/// <summary>
/// The following function will take in a set of mixed bytes and decrypt them, returning them 
/// to the original form. 
/// Given a byte : 00101110
/// Swap as follows: 10010011
/// </summary>
/// <param name="byte"></param>
/// <returns>swappedBytes</returns>
unsigned char unmixBits(unsigned char byte)
{
    // First we have to move the bits that are at the end back to the start
    unsigned char firstTwoBits = (byte & 0x03) << 6;

    // Then we need to move the following bits back to the end
    unsigned char lastFewBits = (byte & 0x1E) >> 2;
    //unsigned char lastFewBits = (byte & 0xFC) >> 2;

    // Move the bits in 2 and 3 back to 4 and 5
    unsigned char bitsFourAndFive = (byte & 0x60) >> 2;

    // flip around bits 4 and 5
    unsigned char newBitFour = (bitsFourAndFive & 0x08) << 1;
    unsigned char newBitFive = (bitsFourAndFive & 0x10) >> 1;

    // Rebuild it
    unsigned char swappedByte = firstTwoBits |  newBitFour | newBitFive | lastFewBits;

    return swappedByte;
}




int main()
{
    // Test Data for swapped bytes
	unsigned char byte = 0x93;
	printf("Original byte: 0x%02X\n", byte);
	
	unsigned char swappedBytes = mixBits(byte);

	printf("Swapped byte: 0x%02X\n", swappedBytes);
    unsigned char originalBytes = unmixBits(swappedBytes);
    printf("Swapping the bytes back: 0x%02X\n", originalBytes);
   


	return EXIT_SUCCESS;
}