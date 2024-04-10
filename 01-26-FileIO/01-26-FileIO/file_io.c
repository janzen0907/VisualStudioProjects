#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "file_io.h"

#define MAX_NAME_SIZE 30


// Study errno.h on Wikipedia before procedding
// There is a global variable called errno that get set to indicate an error
// See also strerror function to get a message associated with the errno. 
int demoOpenClose(const char* cFileName, const char* cFileMode)
{
	// Pointer to a file stream
	FILE* filePtr = NULL;

	// A variable to store potentail error code
	int iErr = EXIT_SUCCESS;

	// Use fopen to opena  file. Note: Returns a FILE pointer that must be assigned
	// If it fails, it returns a NULL and sets the errno variable to indicate an error
	// Parameters are a const char* indicating a path/file name
	// and a const char* indicating the mode (read, write, append).
	filePtr = fopen(cFileName, cFileMode);
	//fopen_s(&filePtr, cFileName, cFileMode); // fopen_s is a pointer to a pointer, so we have to pass in the
	// address of the file pointer
	if (filePtr != NULL)
	{
		// Successfully opened the file
		// Close the file when done
		fclose(filePtr);
		printf("%s was successfully opened and closed \n", cFileName);

	}
	else
	{
		iErr = errno;
		printf("Error accessing file %s: %s\n", cFileName, strerror(iErr));
	}

	return iErr;
}

int demoRead(const char* cFileName, const char* cFileMode)
{
	// Pointer to a file stream
	FILE* filePtr = NULL;

	// A variable to store potential error codes
	int iErr = EXIT_SUCCESS;

	int intChar, retVal; // create two variables on one line
	char cBuffer[MAX_SIZE];
	char* retPtr = NULL;

	/*
	All read operations read data from the file to the memory location indicated (cBuffer)
	Only fgets (and fcsanf for %s) adds an addition null terminator to the data in the buffer
	Return types vary so testing for success depends on the function used.
	fscanf/fread - return number of times assigned or read
	 fscanf returns EOR if a failure occures before teh first assignment
	 fgets - returns a pointer to teh string read or NULL
	 fgetc - returns the character or EOF
	*/
	// Calling fOpen which and assining it to filePTR. Then it checks if filePtr is null
	if ((filePtr = fopen(cFileName, cFileMode)) != NULL)
	{
		// Some varioud ways of reading from a file
//		retVal = fscanf(filePtr, "%s", cBuffer); // Quits reading at first space
//		retPtr = fgets(cBuffer, MAX_SIZE, filePtr);
//		intChar = fgetc(filePtr);
		retVal = fread((void*)cBuffer, sizeof(char), 2, filePtr);

		  if (retVal > 0)
		//if (retPtr != NULL)
		//if (intChar != EOF) // End of file character
		{
			printf("retVal: %d\n", retVal);
			//printf("retPtr: %p\n", retPtr);
			//printf("cBuffer: %p\n", cBuffer);
			printf("cBuffer: %s\n", cBuffer);
			//printf("intChar: %d\n", intChar);
			//printf("intChar: %c\n", intChar);
		}
		else // failed to read
		{
			// Check if the file stream has an error using the ferror function
			if (iErr = ferror(filePtr))
			{
				printf("Error reading from the file %s: %s\n", cFileName, strerror(iErr));
			}
			else // No message, display a generic message
			{
				printf("Could not retrieve data\n");
			}
		}

		fclose(filePtr);
	}
	else // faile to open the file
	{
		iErr = errno;
		printf("Error accessing teh file %s: %s\n", cFileName, strerror(iErr));
	}

	return iErr;
}

int demoWrite(const char* cFileName, const char* cFileMode, const char* cDataPtr)
{
	FILE* fileptr = NULL;
	int iErr = EXIT_SUCCESS;
	int retVal; // Number of writes

	// Taking the results of the fopen function and comparing it to null
	if ((fileptr = fopen(cFileName, cFileMode)) != NULL)
	{
		// fwrite - will return the number of successful items written
		//retVal = fwrite((void*)cDataPtr, sizeof(char), strlen(cDataPtr), fileptr);
		// fprintf
		//retVal = fprintf(fileptr, "%s\nHi\n", cDataPtr);
		// fputs
		//retVal = fputs(cDataPtr, fileptr); // returns 0 if successful
		// fputc
		retVal = fputc(cDataPtr[0], fileptr);


		if (retVal > 0) // if successful
		//if (retVal == 0) // check for success for puts
		{
			printf("File written: %s\n", cFileName);
			printf("retVal: %d\n", retVal);
		}
		else // failed to write
		{
			if (iErr = ferror(fileptr))
			{
				printf("Error writing to file %s: %s\n", cFileName, strerror(iErr));
			}
			else
			{
				printf("Could not write the data\n");
			}
			
		}

		// Close the file when done
		fclose(fileptr);
		printf("%s was successfully opened and closed. \n", cFileName);

	}
	else // failed to open file for writing
	{
		iErr = errno;
		printf("Error accessing the file %s: %s\n", cFileName, strerror(iErr));
	}

	return iErr;
}

int demoWriteBinary(const char* cFileName, const char* cFileMode, int* iDataPtr)
{
	FILE* fileptr = NULL;
	int iErr = EXIT_SUCCESS;
	int retVal; // Number of writes

	if ((fileptr = fopen(cFileName, cFileMode)) != NULL)
	{
		retVal = fwrite((void*)iDataPtr, sizeof(int), 1, fileptr);

		if (retVal > 0) // if successful
		{
			printf("File written: %s\n", cFileName);
			printf("retval: %d\n", retVal);
		}
		else // failed to write 
		{
			// if there is an error number
			if (iErr = ferror(fileptr))
			{
				printf("Error writing to file %s: %s\n", cFileName, strerror(iErr));
			}
			else
			{
				printf("Could not write to the file");
			}
		}

		// Close the file when done
		fclose(fileptr);
		printf("%s was successfully opened and closed \n", cFileName);
	}
	else // failed to open the file for writing
	{
		iErr = errno;
		printf("Error accessing the file %s: %s\n", cFileName, strerror(iErr));
	}
}

// In class Exercise
/*
* use scanf of int
* fgets for string
* Write a function that will write out 3 records of information enterbed by the user
* Each record consists of:
*	SIN# (integer)
*	NAME (char arrar of MAX_NAME_SIZE)
* 
* This information is entered in using scanf (remember to get the \n off the buffer after scanf) 
and fgets from stdin
* (so a space can be included in the name)
* 
* After entering a records, write the data out to a binary file.
* Repeat until 3 records have been written out
* Do some error checking after each write
* Close the file
*/
int exerciseBinaryWrite(const char* cFileName, const char* cFileMode)
{
	FILE* filePtr = NULL;
	int iErr = 0;
	int iSin, retSin, retName;
	char cNameArray[MAX_NAME_SIZE];
	short sNumRecords = NUM_RECORDS;

	if ((filePtr = fopen(cFileName, cFileMode)) != NULL)
	{
		// Write out the number of records
		// Could check return value to check for a successful write
		fwrite((void*)&sNumRecords, sizeof(short), 1, filePtr);

		for (int var = 0; var < NUM_RECORDS; var++)
		{
			// Prompt user for SIN number
			printf("Enter SIN number: ");
			scanf("%d", &iSin); // or "%i" - same as "%d"

			// Clear the stdin buffer of the newline character
			// Note that this will only work if user hit return immediately after
			// entering the SIN, not if there are more characters - could use loop instead
			getc(stdin);

			// Get the name
			printf("Enter the name: ");
			// Safe way to get a string - however, fgets reads in the newline!
			//fgets(cNameArray, MAX_NAME_SIZE, stdin);
			gets_s(cNameArray, MAX_NAME_SIZE);

			retSin = fwrite((void*)&iSin, sizeof(int), 1, filePtr);
			retName = fwrite((void*)cNameArray, sizeof(char) * MAX_NAME_SIZE, 1, filePtr);

			if (retSin == 0 || retName == 0)
			{
				if (iErr = ferror(filePtr))
				{
					printf("Error writing the file %s: %s\n", cFileName, strerror(iErr));
				}
				else
				{
					printf("Could not write data\n");
				}
			}
		}

		fclose(filePtr);
	}
	else // failed to open file
	{
		iErr = errno;
		printf("Error accessing the file %s: %s\n", cFileName, strerror(iErr));
	}

	return iErr;
}


int exerciseBinaryRead(const char* cFileName, const char* cFileMode, int iSeek)
{
	FILE* filePtr = NULL;
	int iErr = 0;
	int iSin, retSin, retName;
	char cNameArray[MAX_NAME_SIZE];
	short sNumRecords = 0;
	int found = 0;

	if ((filePtr = fopen(cFileName, cFileMode)) != NULL)
	{
		// Read in the number of records
		fread((void*)&sNumRecords, sizeof(short), 1, filePtr);

		// Loop through the records
		for (int var = 0; var < sNumRecords && !found; var++)
		{
			// Read in the SIN#
			fread((void*)&iSin, sizeof(int), 1, filePtr);
			if (iSin == iSeek)
			{
				// Read the name in from the file, quit looping as well
				found = fread((void*)cNameArray, sizeof(char) * MAX_NAME_SIZE, 1, filePtr);
				printf("SIN %d has name %s\n", iSin, cNameArray);
			}
			else
			{
				fseek(filePtr, MAX_NAME_SIZE, SEEK_CUR);
			}
		}
		if (!found)
		{
			printf("SIN# not found\n");
		}
		// Close the file
		fclose(filePtr);
	}
	else
	{
		printf("Could not open file\n");
	}

	// Not really setting this yet, but you (the student) can do this boring task as an exercise
	return iErr;
}