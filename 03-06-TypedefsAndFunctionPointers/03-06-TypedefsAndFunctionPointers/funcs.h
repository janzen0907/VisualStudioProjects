#ifndef FUNCS_H
#define FUNCS_H

typedef int Length;
typedef char* String;
typedef unsigned short UShort;

// Define a function pointer type.
// Define the signature for the function pointer.
// The part in all caps is the function pointer type.
// The function pointer returns an int and takes an int.
typedef int (*FNPTR_TYPE)(int);

// The COMPARER function returns an int and takes in two ints.
typedef int (*COMPARER)(int, int);

void iterateNumbers(int iArray[], int iSize, FNPTR_TYPE myFunc);

void sortInts(int iArray[], int iSize, COMPARER comp);

#endif // !FUNCS_H
