#ifndef STRUCTS_H
#define STRUCTS_H

#define NAME_SIZE		5
#define MAX_NAME_SIZE	256

// Structs are generally defined in a header file

// How to define a struct without a typedef.
// We rarely create structs this way - too cumbersome.
struct BirthDate
{
	// Attributes
	char cName[NAME_SIZE];
	char cGender;
	int day;
	int month;
	int year;
};

#pragma pack(push) // Used to store the default byte alignment
#pragma pack(1) // Set the byte alignment to 1
// Example of declaring a struct using typedef
typedef struct
{
	// Attributes
	char cName[NAME_SIZE];
	char cGender;
	int day;
	int month;
	int year;
} BirthDateTD;
#pragma pack(pop) // Used to restore the default byte alignment

typedef struct
{
	// Some of the attributes are dynamically allocated
	char* cNamePtr;
	int iStudentNum;

	// Array of marks
	int* iMarksPtr;
	// Number of marks in the marks array
	int iMarksCount;
} student;

typedef struct
{
	// A dynamically allocated array of student pointers
	student** sPtrPtr;
	// How many students are in the classroom
	unsigned short sNumStudents;
} classroom;


/*
A union is a data type that is similar in syntax to a struct. A union
can have several attributes; however, only one is assigned at a time.
The memory reserved by a union is equal to that of its largest member.

Example: Suppose we want to store how much fertilizer a farmer purchased.
Fertilizer is stored in various units. The following union could be used
to store the amount purchased.
*/
typedef union
{
	unsigned char truckloads;
	unsigned int bags;
	double tons;
} FertilizerQuantity;

typedef struct {
	unsigned char a; // transparency value (or alpha channel)
	unsigned char b;
	unsigned char g;
	unsigned char r;
} pixel32;

typedef union {
	// This is 4 bytes
	unsigned int val;
	// This is also 4 bytes
	pixel32 components;
} colorVal;

#pragma pack(push)
#pragma pack(1)
typedef struct {
	char id[10];
	char ramUnit;
	int ramSize;
	char* descriptionPtr;
} Computer;
#pragma pack(pop)

typedef union {
	long long int bytes;
	int megabytes;
	short gigabytes;
	char terabytes;
} MemorySize;


void DisplayBirthDateBasic(struct BirthDate bd);
void DisplayBirthDateTypedef(BirthDateTD bd);
void AlterBirthDate(BirthDateTD bd);
void AlterBirthDateByRef(BirthDateTD* bdPtr);

// A function that creates a student and initializes the attributes.
// This is similar to the keyword new in C# or Java. It allocates the instance
// AND it is also like a constructor that sets all the attributes.
student* CreateStudent(char* cNamePtr, int iStudentNum, int* iMarksPtr, int iMarkCount);

// A function to display the data stored in a student instance.
// Takes a student instance, not a pointer. Sometimes this is done as a copy
// of the student is made. If this function messes up the struct somehow, it
// will not mess up the struct passed in.
void DisplayStudent(student s);

// This function will free the memory allocated for a student instance.
// In C++, there is a function called a destructor where the programmer is
// supposed to release memory and clean up any other resources - this is similar.
void FreeStudent(student* sPtr);

// Get student data from the user
student* GetStudent();

// Ask the user to populate the classroom. First ask how many students.
// Then ask for data for each student.
classroom PopulateClassroom();

// Display each student in the classroom
void DisplayClassroom(classroom c);

// Free memory associated with classroom
void FreeClassroom(classroom* classPtr);

#endif
