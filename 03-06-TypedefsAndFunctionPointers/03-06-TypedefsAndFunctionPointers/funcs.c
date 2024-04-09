#include <stdio.h>
#include "funcs.h"

void iterateNumbers(int iArray[], int iSize, FNPTR_TYPE myFunc)
{
	int iVal = 0;

	for (int i = 0; i < iSize; i++)
	{
		iVal = myFunc(iArray[i]); // use myFunc like any other function
		printf("The value %d after the operation is %d\n", iArray[i], iVal);
	}
	printf("\n");
}


// Insertion sort from https://www.geeksforgeeks.org/Insertion-sort
// comp should return > 0 when item is higher in the sort order
void sortInts(int iArray[], int iSize, COMPARER comp)
{
	int i, key, j;

	for (i = 1; i < iSize; i++)
	{
		key = iArray[i];
		j = i - 1;

		while (j >= 0 && comp(iArray[j], key) > 0)
		{
			iArray[j + 1] = iArray[j];
			j = j - 1;
		}
		iArray[j + 1] = key;
	}
}
