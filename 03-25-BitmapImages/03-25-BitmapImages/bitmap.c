#define _CRT_SECURE_NO_WARNINGS // to use older functions like fopen instead of fopen_s
#include <stdlib.h> // for malloc
#include <string.h>
#include "bitmap.h"
#include <math.h> // for sin and cos

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

//NOTE: THIS IS BROKEN GET MICHAELS CODE FROM ONEDRIVE
// Given an image and an upper left and lower right coordinate, crop the image
// Parameters:
// imgPtr -> a pointer to the image to crop
// xLeft -> column value of the left coord
// yLeft -> row value of the left coord
// xRight -> column value of the right coord
// yRight -> row value of the right coord
// Returns: the cropped image
IMAGE Crop(IMAGE* imgPtr, int xLeft, int yLeft, int xRight, int yRight)
{
	int i, j, padding;
	DWORD imageSize;
	IMAGE tmpImg = { NULL, NULL };

	// If the cropped image's header was allocated
	if (tmpImg.bmHDR = (BITMAPHDR*)malloc(sizeof(BITMAPHDR))) // != NULL
	{
		// Copy the header info from the original image to the cropped image
		memcpy(tmpImg.bmHDR, imgPtr->bmHDR, sizeof(BITMAPHDR));
		// Set the height and width of the cropped image
		tmpImg.bmHDR->dwWidth = xRight - xLeft;
		tmpImg.bmHDR->dwHeight = yRight - yLeft;

		// Calculate the padding of the cropped image
		padding = tmpImg.bmHDR->dwWidth % 4;
		imageSize = (tmpImg.bmHDR->dwWidth * sizeof(PIXEL) + padding) * tmpImg.bmHDR->dwHeight;

		tmpImg.bmHDR->dwImageSize = imageSize;
		tmpImg.bmHDR->dwFileSize = imageSize + sizeof(BITMAPHDR);

		// If memory for the cropped image was allocated
		if (tmpImg.bmData = (PIXEL*)malloc(imageSize)) // != NULL
		{
			// For each row in the cropped image
			for (i = 0; i < tmpImg.bmHDR->dwHeight; i++)
			{
				// For each column in the cropped image
				for (j = 0; j < tmpImg.bmHDR->dwWidth; i++)
				{
					*GetPixel(i, j, &tmpImg) = *(GetPixel(yLeft + i, xLeft + j , imgPtr));
				}
			}
		}
		else
		{
			free(tmpImg.bmHDR);
			tmpImg.bmHDR = NULL;
		}

	}
	return tmpImg;
}

// Also not working, get solution from OneDrive
// Given an image and an angle in radians, rotate the image counterclockwise.
IMAGE Rotate(IMAGE* imgPtr, double theata)
{
	DWORD imageSize = 0, padding = 0;
	IMAGE img = { NULL, NULL };
	PIXEL startPixel = { 0 , 255, 128 }; // crazy color to make anti-aliasing easier

	// Allocate space for the header
	img.bmHDR = (BITMAPHDR*)malloc(sizeof(BITMAPHDR));
	if (img.bmHDR)
	{
		memcpy(img.bmHDR, imgPtr->bmHDR, sizeof(BITMAPHDR));

		// Need to get the image size
		imageSize = imgPtr->bmHDR->dwImageSize;
		img.bmData = (PIXEL*)malloc(imageSize);

		if (img.bmData)
		{
			// Initialize background to crazy color
			InitializePixelData(&img, startPixel);

			// Determine the center of rotation (middle of image)
			// Halfway through the height and width
			int oX = imgPtr->bmHDR->dwWidth / 2;
			int oY = imgPtr->bmHDR->dwHeight / 2;

			// Copy pixel to new image
			for (int pY = 0; pY < imgPtr->bmHDR->dwHeight; pY++)
			{
				for (int pX = 0; pX < imgPtr->bmHDR->dwWidth; pX++)
				{
					// Calculate position of the current pixel in the new image
					int x = (int)cos(theata) * (pX - oX) - sin(theata) * (pY - oY) + oX;
					int y = (int)sin(theata) * (pX - oX) + cos(theata) * (pY - oY) + oY;

					// If it is in bounds, assign to the new image
					if (x >= 0 && x < img.bmHDR->dwWidth && y >= 0 && y < img.bmHDR->dwHeight)
					{
						*GetPixel(y, x, &img) = *GetPixel(pY, pX, imgPtr);
					}
				}
			}
			AntiAlias(&img);
		}
		else // If there was a problem allocationg memory, release memory that was allocated
		{
			free(img.bmHDR);
			img.bmHDR = NULL;
			printf("Failed to allocate data\n");
		}

	}

	return img;
}


/*
* Purpose: Roating the object leaves "holes" in teh rotated image. This function
*			looks for those holes and fills them with teh average of its neighbours if they exist.
*			Code assumes that the backgroud was "pre-initialized" to the given background color.
*/
void AntiAlias(IMAGE* imgPtr)
{
	PIXEL p = { 0, 255, 128 }; // crazy colour to make AA easier
	PIXEL* pCurrent = NULL;
	PIXEL* pLeft = NULL;
	PIXEL* pRight = NULL;

	// If the image is not null
	if (imgPtr != NULL)
	{
		// If the image header and data are not null
		if (imgPtr->bmHDR != NULL && imgPtr->bmData != NULL)
		{
			// Loop throught the array of pixels
			for (int i = 0; i < imgPtr->bmHDR->dwHeight; i++)
			{
				for (int j = 0; j < imgPtr->bmHDR->dwWidth; j++)
				{
					pCurrent = GetPixel(i, j, imgPtr);

					// If pixel is the background color
					if (memcmp(pCurrent, &p, sizeof(PIXEL)) == 0)
					{
						// Get left pixel if it exists
						if (j > 0)
						{
							pLeft = GetPixel(i, j - 1, imgPtr);
						}
						// Get right pixel if it exists
						if (j < imgPtr->bmHDR->dwWidth - 1)
						{
							pRight = GetPixel(i, j + 1, imgPtr);
						}

						// If both exist
						if (pLeft && pRight) // != null
						{
							pCurrent->bBlu = pLeft->bBlu / 2 + pRight->bBlu / 2;
							pCurrent->bGrn = pLeft->bGrn / 2 + pRight->bGrn / 2;
							pCurrent->bRed = pLeft->bRed / 2 + pRight->bRed / 2;
						}
						// If only the left exists
						else if (pLeft)
						{
							pCurrent->bBlu = pLeft->bBlu;
							pCurrent->bGrn = pLeft->bGrn;
							pCurrent->bRed = pLeft->bRed;
						}
						// If only the right exists
						else if (pRight)
						{
							pCurrent->bBlu = pRight->bBlu;
							pCurrent->bGrn = pRight->bGrn;
							pCurrent->bRed = pRight->bRed;
						}
						// Reset the pixels
						pLeft = NULL;
						pRight = NULL;
					}
				}
			}
		}
	}

}

/*
* Purose: Given an image and an angle in radians, rotate that image counterclockwise
*			in a larger canvas.
* Parameters: imgPtr -> an image to rotate
*				theta -> an image measured in radians
* Returns:		rotated image
*/
IMAGE FancyRotateImage(IMAGE* imgPtr, double theta)
{
	IMAGE img = { NULL, NULL };
	PIXEL startPixel = { 0, 255, 128 }; // Crazy color to make AA easier

	// Allocate space for the header
	img.bmHDR = (BITMAPHDR*)malloc(sizeof(BITMAPHDR));
	memcpy(img.bmHDR, imgPtr->bmHDR, sizeof(BITMAPHDR));

	// Allocare spcae for the image
	DWORD imageSize = 0, padding = 0;

	// Determine the center of rotation (middle of image)
	int oX = imgPtr->bmHDR->dwWidth / 2;
	int oY = imgPtr->bmHDR->dwHeight / 2;

	// Wouldn't be expected to do this
	double alpha = atan(oY / (double)oX);

	// Calculate the diagonal size of het image that will be maximum height/width of rotated image
	int maxDimension = (int)ceil(sqrt(4.0 * oX * oX + 4.0 * oY * oY));

	// Convert the "theta" back to degrees, then modulus it by 360, store the result in "angle"
	// The "angle" will determine which quadrant the width size of the image roates into.
	// It, in turn determines the formula for calculating the exact width and height of the 
	// rotated image in order to not lose any pixe;s
	int angle = (int)ceil(theta * 180.0 / PI) % 360;
	if (angle <= 90 || (angle > 180 && angle <= 270))
	{
		img.bmHDR->dwWidth = abs(maxDimension * cos(-alpha + theta));
		img.bmHDR->dwHeight = abs(ceil(maxDimension * sin(alpha + theta)));
	}
	else
	{
		img.bmHDR->dwHeight = abs(maxDimension * sin(-alpha + theta));
		img.bmHDR->dwHeight = abs(ceil(maxDimension * cos(alpha + theta)));
	}
	// Calculate the padding 
	padding = img.bmHDR->dwWidth % 4;
	// Calculate the image size = # of rows * size of each row
	imageSize = img.bmHDR->dwHeight * (sizeof(PIXEL) * img.bmHDR->dwWidth + padding);

	img.bmHDR->dwImageSize = imageSize;
	img.bmHDR->dwFileSize = imageSize + sizeof(BITMAPHDR);

	img.bmData = (PIXEL*)malloc(imageSize);

	// Initialize background to crazy color
	InitializePixelData(&img, startPixel);

	// Copy pixels to teh new image
	for (int pY = 0; pY < imgPtr->bmHDR->dwHeight; pY++)
	{
		for (int pX = 0; pX < imgPtr->bmHDR->dwWidth; pX++)
		{
			// Calculate posistion of the current pixel in the new image
			// Due to the increased width and height, x needs to be translated by (dwWidth/2 - oX)
			// and y needs to be translated to (dwHeight2 -oY)
			int x = (int)(cos(theta) * (pX - oX) - sin(theta) * (pY - oY) + oX + img.bmHDR->dwWidth / 2.0 - oX);
			int y = (int)(sin(theta) * (pX - oX) + cos(theta) * (pY - oY) + oY + img.bmHDR->dwHeight / 2.0 - oY);

			if (x >= 0 && x < img.bmHDR->dwWidth && y >= 0 && y < img.bmHDR->dwHeight)
			{
				*GetPixel(y, x, &img) = *GetPixel(pY, pX, imgPtr);
			}
		}
	}

	AntiAlias(&img);

	return img;
}
