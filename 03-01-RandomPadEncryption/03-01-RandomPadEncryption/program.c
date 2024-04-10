/*
	Filename:	program.c
	Author:		Sample Solution (solution9999)
	Course:		COSC 292 (Advanced Programming 2)
	Instructor:	Michael Grzesina
	Date:		Winter 2024
	Purpose:	Practice XOR by creating a program to encode/decode files
				using random pad encryption
*/

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE	256


/*
	Function:	encryptMessage
	Purpose:	Take bytes from an input file and a pad file and combine them
				using XOR and then save them to an output file
	Parameters:	inputFile - file pointer to opened input file (for reading)
				outputFile - file pointer to opened output file (for writing)
				padFile - file pointer to opened pad file (for reading)
	Returns:	Nothing
	Changes:	outputFile to an encrypted or unencrypted message
	Assumptions:	padFile contains at least as many bytes as inputFile
*/
void encryptMessage(FILE* inputFile, FILE* outputFile, FILE* padFile)
{
	int inputChar, padChar, outputChar;

	inputChar = fgetc(inputFile); // prime the loop by trying to read
	while (!feof(inputFile)) // while we haven't reached the end of the file
	{
		padChar = fgetc(padFile); // get the pad byte
		outputChar = inputChar ^ padChar; // XOR with the input byte
		fputc(outputChar, outputFile); // write out encrypted / decrypted byte
		inputChar = fgetc(inputFile); // try to read the next byte
	}
}


/*
	Function:	main
	Purpose:	Run program that will ask for an input filename and an output
				filename and open the input file (for reading), the output file
				(for writing), and the file "random.pad" (for reading), 
				to be used by an encryption function.
	Parameters:	argc - number of command-line arguments (not used)
				argv - array of command-line arguments (not used)
	Returns:	0 (EXIT_SUCCESS) if program exits successfully
	Changes:	Nothing
	Assumptions:	Files exist or are created in the proper folder
*/
int main(int argc, char** argv)
{
	char fileName[BUFFER_SIZE];
	FILE* inputFile = NULL;
	FILE* outputFile = NULL;
	FILE* padFile = NULL;
	int err;

	printf("Enter an input filename: ");
	gets_s(fileName, BUFFER_SIZE);
	err = fopen_s(&inputFile, fileName, "rb");
	if (err == 0)
	{
		printf("Enter an output filename: ");
		gets_s(fileName, BUFFER_SIZE);
		err = fopen_s(&outputFile, fileName, "wb");
		if (err == 0)
		{
			err = fopen_s(&padFile, "random.pad", "rb");
			if (err == 0)
			{
				encryptMessage(inputFile, outputFile, padFile);
				fclose(padFile);
			}
			else
			{
				fprintf(stderr, "Couldn't open random pad\n");
			}
			fclose(outputFile);
		}
		else
		{
			fprintf(stderr, "Couldn't create output file\n");
		}
		fclose(inputFile);
	}
	else
	{
		fprintf(stderr, "Couldn't read input file\n");
	}

	return EXIT_SUCCESS;
}