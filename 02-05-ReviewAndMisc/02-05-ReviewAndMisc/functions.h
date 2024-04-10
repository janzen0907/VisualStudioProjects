#ifndef FUNCTIONS_H // header guard - make sure file is only added once
					// if FUNCTIONS_H is already defined, skip the file
#define FUNCTIONS_H // if FUNCTIONS_H was not defined, define it so teh file will be skipped next time

#define PASSING_GRADE	50
#define BUFFER_SIZE		100
#define MAX_NAME_SIZE	40

void modify_my_array(unsigned short int* sArrayPtr, int iArraySize);

// Get a grade and upadte the global count of grades - returns the grade
int getGradeGlobal();

// Get a grade and update the count of grades- returns the grade
int getGradeLocal();

// Get the grade and update the count of grades passed in - returns the grade
int getGradePassByRef(int* iCountPtr);

// Asks for # and name and write records to file passed in
void writeData(FILE* filePtr);

// Read the records and display them
void readData(FILE* filePtr);

#endif // !FUNCTIONS_H