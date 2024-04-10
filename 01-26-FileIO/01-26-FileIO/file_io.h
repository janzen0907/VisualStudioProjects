#pragma once

#define MAX_SIZE	100
#define NUM_RECORDS 3


int demoOpenClose(const char*, const char*);
int demoRead(const char*, const char*);
int demoWrite(const char* cFileName, const char* cFileMode, const char* cDataPtr);
int demoWriteBinary(const char*, const char*, int*);
int exerciseBinaryWrite(const char* cFileName, const char* cFileMode);
int exerciseBinaryRead(const char* cFileName, const char* cFileMode, int iSeek);
