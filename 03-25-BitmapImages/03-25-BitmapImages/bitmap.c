#define _CRT_SECURE_NO_WARNINGS // to use older functions like fopen instead of fopen_s
#include <stdlib.h> // for malloc
#include <string.h>
#include "bitmap.h"

#define MAX_FILENAME_SIZE	256


FILE* GetFile(const char* cPrompt, const char* cMode)
{
	FILE* aFile = NULL;
	char cFileName[MAX_FILENAME_SIZE];

	// Get the name from the user
	printf("%s", cPrompt);
	gets_s(cFileName, MAX_FILENAME_SIZE);

	// Open the file with the given name and mode passed in
	aFile = fopen(cFileName, cMode);

	return aFile;
}


void ReadImage(IMAGE* imgPtr, FILE* infile)
{
	// Read in the header
	ReadHeader(imgPtr, infile);

	if (imgPtr->bmHDR != NULL)
	{
		// Read in the data
		ReadData(imgPtr, infile);
	}
}


void ReadHeader(IMAGE* imgPtr, FILE* infile)
{
	// Allocate memory for the bitmap header
	imgPtr->bmHDR = (BITMAPHDR*)malloc(sizeof(BITMAPHDR));

	if (imgPtr->bmHDR != NULL)
	{
		if (fread(imgPtr->bmHDR, sizeof(BITMAPHDR), 1, infile) != 1)
		{
			// No success reading, but malloc worked
			// Free the memory
			free(imgPtr->bmHDR);
			imgPtr->bmHDR = NULL;
			printf("Reading header from file did not work\n");
		}
	}
}


void PrintHeader(BITMAPHDR* headerPtr)
{
	printf("First two characters: %x\n", headerPtr->wType); // should be 0x4D42
	printf("File size: %d\n", headerPtr->dwFileSize);
	printf("Data offset: %d\n", headerPtr->dwDataOffset); // should be 54
	printf("Header size: %d\n", headerPtr->dwHeaderSize); // should be 40
	printf("Dimensions: %d by %d\n", headerPtr->dwWidth, headerPtr->dwHeight);
	printf("Planes: %d\n", headerPtr->wPlanes); // should be 1
	printf("Color depth: %d\n", headerPtr->wBitCount); // should be 24
	printf("Compression: %d\n", headerPtr->dwCompression);
	printf("Image size: %d\n", headerPtr->dwImageSize);
	printf("Colors used: %d\n", headerPtr->dwClrUsed);
}


void ReadData(IMAGE* imgPtr, FILE* infile)
{
	// The padding, in bytes, for the image is:
	unsigned int padding = imgPtr->bmHDR->dwWidth % 4;
	// Calculate the image size in bytes = size of row * number of rows
	unsigned int imageSize = (imgPtr->bmHDR->dwWidth * sizeof(PIXEL) + padding)
		* imgPtr->bmHDR->dwHeight;

	printf("Calculated image data size: %d\n", imageSize);

	// Allocate memory for pixel data
	imgPtr->bmData = (PIXEL*)malloc(imageSize);
	if (imgPtr->bmData != NULL)
	{
		// Read in the pixel array from the file
		if (fread(imgPtr->bmData, imageSize, 1, infile) != 1)
		{
			// Failed to read in the image data
			FreeImage(imgPtr);
			printf("Reading data from file did not work\n");
		}
	}
	else
	{
		free(imgPtr->bmHDR);
		imgPtr->bmHDR = NULL;
	}
}


void WriteImage(IMAGE* imgPtr, FILE* outfile)
{
	// The padding, in bytes, for the image is:
	unsigned int padding = imgPtr->bmHDR->dwWidth % 4;
	// Calculate the image size in bytes = size of row * number of rows
	unsigned int imageSize = (imgPtr->bmHDR->dwWidth * sizeof(PIXEL) + padding)
		* imgPtr->bmHDR->dwHeight;

	// Write the header
	if (fwrite(imgPtr->bmHDR, sizeof(BITMAPHDR), 1, outfile) != 1)
	{
		printf("Failed to write image header\n");
	}
	else
	{
		// Write the image data
		if (fwrite(imgPtr->bmData, imageSize, 1, outfile) != 1)
		{
			printf("Failed to write image data\n");
		}
	}
}


void FreeImage(IMAGE* imgPtr)
{
	// Free the image
	free(imgPtr->bmHDR);
	imgPtr->bmHDR = NULL;
	if (imgPtr->bmData != NULL)
	{
		free(imgPtr->bmData);
		imgPtr->bmData = NULL;
	}
}


// Manipulate each pixel in a bitmap image provided using the function provided
void ManipulateImage(IMAGE* imgPtr, BM_FUNC_PTR pixelFunc)
{
	PIXEL* currentPixel = imgPtr->bmData;
	// The padding, in bytes, for the image is:
	unsigned int padding = imgPtr->bmHDR->dwWidth % 4;

	for (int i = 0; i < imgPtr->bmHDR->dwHeight; i++) // for every row
	{
		for (int j = 0; j < imgPtr->bmHDR->dwWidth; j++) // for each pixel
		{
			pixelFunc(currentPixel); // manipulate that pixel
			currentPixel++; // move to the next pixel
		}
		// At the end of the row, move padding BYTEs forward
		currentPixel = (PIXEL*)((BYTE*)currentPixel + padding);
	}
}

// Helper function to get a pixel pointer from a particualar spot in an image
PIXEL* GetPixel(int row, int col, IMAGE* imgptr)
{
	unsigned int padding = imgptr->bmHDR->dwWidth % 4;

	// Offset in bytes = size of the row in bytes * number of rows
	// + number of bytes precedding the desired pixel in the row
	unsigned int offset = (imgptr->bmHDR->dwWidth * sizeof(PIXEL) + padding) * row
		+ col * sizeof(PIXEL);

	// Offset is in bytes, so we need to do some casting of pointers
	return (PIXEL*)((BYTE*)imgptr->bmData + offset);
}

// Combine pixels from two bitmap images provided using the function provided
void ManipulateTwoImages(IMAGE* img1, IMAGE* img2, BM_TWO_PIXELS twoPixelFunc)
{
	// Have to consider that the size of the 2 images may not be the same
	int height = (img1->bmHDR->dwHeight < img2->bmHDR->dwHeight) ?
		img1->bmHDR->dwHeight : img2->bmHDR->dwHeight;
	int width = (img1->bmHDR->dwWidth < img2->bmHDR->dwWidth) ?
		img2->bmHDR->dwWidth : img2->bmHDR->dwWidth;

	// Goal: Go through each pixel and call the twoPixelFunc on the pixels
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			twoPixelFunc(GetPixel(i, j, img1), GetPixel(i,j,img2));
		}
	}
}
/// <summary>
/// Purpose: Given an image with new dynamically allocated data, initialize each pixel
/// to some background color
/// Parameters: 
/// imgPtr -> An Image with no pixel values set
/// desiredPixel -> a pixel (set of colors) to assign to each pixel in the image
/// </summary>
void InitializePixelData(IMAGE* imgPtr, PIXEL desiredPixel)
{
	PIXEL* pixelPtr = imgPtr->bmData;
	unsigned int padding = imgPtr->bmHDR->dwWidth % 4;

	// Loop through the array of pixels
	for (int i = 0; i < imgPtr->bmHDR->dwHeight; i++)
	{
		for (int j = 0; j < imgPtr->bmHDR->dwWidth; j++)
		{
			//*GetPixel(i, j, imgPtr) = desiredPixel;
			*pixelPtr = desiredPixel;
			pixelPtr++;

		}
		pixelPtr = (PIXEL*)((BYTE*)pixelPtr + padding);
	}
}

// Resize the canvas of an image to the width and height given
IMAGE ResizeCanvas(IMAGE* originalImgPtr, int newWidth, int newHeight)
{
	IMAGE imgNew = { NULL, NULL };
	int newImageSize = 0;
	int padding = 0;
	int width, height;
	PIXEL startPixel = { 255, 255, 255 }; // white pixel

	imgNew.bmHDR = (BITMAPHDR*)malloc(sizeof(BITMAPHDR));
	if (imgNew.bmHDR) // != NULL
	{
		memcpy(imgNew.bmHDR, originalImgPtr->bmHDR, sizeof(BITMAPHDR));
		imgNew.bmHDR->dwWidth = newWidth;
		imgNew.bmHDR->dwHeight = newHeight;

		padding = newWidth % 4;
		newImageSize = (newWidth * sizeof(PIXEL) + padding) * newHeight;

		imgNew.bmHDR->dwImageSize = newImageSize;
		imgNew.bmHDR->dwFileSize = newImageSize + sizeof(BITMAPHDR);

		imgNew.bmData = (PIXEL*)malloc(newImageSize);
		if (imgNew.bmData) // != NULL
		{
			// Initialize all pixels to a chosen color
			InitializePixelData(&imgNew, startPixel);


			height = (newHeight < originalImgPtr->bmHDR->dwHeight) ?
				newHeight : originalImgPtr->bmHDR->dwHeight;
			width = (newWidth < originalImgPtr->bmHDR->dwWidth) ?
				newWidth: originalImgPtr->bmHDR->dwWidth;

			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					*GetPixel(i, j, &imgNew) = *GetPixel(i, j , originalImgPtr);
				}
			}
		}
		else
		{
			free(imgNew.bmHDR);
			imgNew.bmHDR = NULL;
		}
	}
	return imgNew;
}

IMAGE Crop(IMAGE* imgPtr, int xLeft, int yLeft, int xRight, int yRight)
{
	IMAGE imgNew = { NULL, NULL};
	int newImageSize = 0;
	int padding = 0;
	int height, width;
	PIXEL startPixel = { 255, 255, 255 }; // white pixel
	int iWidth = xLeft + yLeft;
	int iHeight = xRight + yRight;

	imgNew.bmHDR = (BITMAPHDR*)malloc(sizeof(BITMAPHDR));
	if (imgNew.bmHDR) // != NULL
	{
		memcpy(imgNew.bmHDR, imgPtr->bmHDR, sizeof(BITMAPHDR));
		imgNew.bmHDR->dwWidth = iWidth;
		imgNew.bmHDR->dwHeight = iHeight;

		padding = xLeft % 4;
		newImageSize = (xLeft * sizeof(PIXEL) + padding) * iHeight;

		imgNew.bmHDR->dwImageSize = newImageSize;
		imgNew.bmHDR->dwFileSize = newImageSize + sizeof(BITMAPHDR);

		imgNew.bmData = (PIXEL*)malloc(newImageSize);
		if (imgNew.bmData) // != NULL
		{
			// Initialize all pixels to a chosen color
			InitializePixelData(&imgNew, startPixel);


			height = (iHeight < imgPtr->bmHDR->dwHeight) ?
				iHeight : imgPtr->bmHDR->dwHeight;
			width = (iWidth < imgPtr->bmHDR->dwWidth) ?
				iWidth : imgPtr->bmHDR->dwWidth;

			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					*GetPixel(i, j, &imgNew) = *GetPixel(i, j, imgPtr);
				}
			}
		}
		else
		{
			free(imgNew.bmHDR);
			imgNew.bmHDR = NULL;
		}
	}
	return imgNew;
}
