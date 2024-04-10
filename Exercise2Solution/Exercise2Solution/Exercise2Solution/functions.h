/*
	Filename:	functions.h
	Author:		Sample Solution
	Course:		COSC 292 (Advanced Programming 2)
	Instructor:	Michael Grzesina
	Date:		Winter 2024
	Purpose:	Header file for practice using pointers and arrays in C
*/

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#define	ARRAY_SIZE	4

void swap(int* p1, int* p2);
int* newInteger();
void hideString(int* iArrPtr, char* cArrPtr);
void unHideString(int* iArrPtr);

#endif // !FUNCTIONS_H_
