#ifndef BITMAP_H
#define BITMAP_H

#include <stdio.h>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;


#pragma pack(push) // Used to store the default byte alignment
#pragma pack(1) // Set the byte alignment to 1

typedef struct
{
	// Bitmap file header - 14 bytes
	WORD wType; // Should be 'B' 'M'
	DWORD dwFileSize;
	WORD wReserved1;
	WORD wReserved2;
	DWORD dwDataOffset; // Should be 54 for our application
	// DIB header (bitmap information header)
	DWORD dwHeaderSize; // Should be 40 for our application
	int dwWidth;
	int dwHeight;
	WORD wPlanes; // Should be 1
	WORD wBitCount; // Should be 24 for our application
	DWORD dwCompression;
	DWORD dwImageSize;
	int dwXPelsPerMeter;
	int dwYPelsPerMeter;
	DWORD dwClrUsed;
	DWORD dwClrImportant;
} BITMAPHDR;

typedef struct
{
	// Strangely, blue comes first in the pixel...
	BYTE bBlu, bGrn, bRed;
} PIXEL;

// A struct that represents the entire image
typedef struct
{
	BITMAPHDR* bmHDR;
	PIXEL* bmData;
} IMAGE;

#pragma pack(pop) // Used to reset the default byte alignment


// Function pointers for editing a bitmap image
typedef void (*BM_FUNC_PTR)(PIXEL*);
typedef void(*BM_TWO_PIXELS)(PIXEL*, PIXEL*);



// Open a file given a prompt from the user (for the type of file) and a file mode
FILE* GetFile(const char* cPrompt, const char* cMode);

// Read an image into the image pointer provided from the already opened file pointer
void ReadImage(IMAGE* imgPtr, FILE* infile);

// Read the image header into the image pointer provided from the already opened file pointer
void ReadHeader(IMAGE* imgPtr, FILE* infile);

// Print out various header values to check if they have been correctly read in
void PrintHeader(BITMAPHDR* headerPtr);

// Read the image data into the image pointer provided from the already opened file pointer
void ReadData(IMAGE* imgPtr, FILE* infile);

// Write the image header and image data from the image pointer provided
// into the already opened file
void WriteImage(IMAGE* imgPtr, FILE* outfile);

// Free the image header and image data from the passed-in image pointer
void FreeImage(IMAGE* imgPtr);

// Manipulate each pixel in a bitmap image provided using the function provided
void ManipulateImage(IMAGE* imgPtr, BM_FUNC_PTR pixelFunc);

// Combine pixels from two bitmap images provided using the function provided
void ManipulateTwoImages(IMAGE* img1, IMAGE* img2, BM_TWO_PIXELS twoPixelFunc);

// Helper function to get a pixel pointer from a particualar spot in an image
PIXEL* GetPixel(int row, int col, IMAGE* imgptr);

// Resize the canvas of an image to the width and height given
IMAGE ResizeCanvas(IMAGE* originalImgPtr, int newWidth, int newHeight);

/// Purpose: Given an image with new dynamically allocated data, initialize each pixel
/// to some background color
void InitializePixelData(IMAGE* imgPtr, PIXEL desiredPixel);


IMAGE Crop(IMAGE* imgPtr, int xLeft, int yLeft, int xRight, int yRight);


#endif // !BITMAP_H
