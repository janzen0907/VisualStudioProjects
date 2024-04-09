#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "bitmap.h"


void GrayscaleAverage(PIXEL* pixelPtr)
{
	BYTE gray = (pixelPtr->bBlu + pixelPtr->bGrn + pixelPtr->bRed) / 3;

	pixelPtr->bBlu = gray;
	pixelPtr->bGrn = gray;
	pixelPtr->bRed = gray;
}


// Write more pixel functions and try to manipulate the image with each of them
// 1: Write a GrayscaleFormula function that will calculate the gray level using
//    the formula 11% * blue + 59% * green + 30% * red
// 2: Write a Negative function that will flip all the bits in each of the blue,
//    green, and red colors (or reverse the intensity of the blue/green/red colors)
// 3: Shift the bits of each color over to the right by 1 to "ghost" the image darker
// 4: Shift the bits of each color over to the right by 2 and make the two bits that
//    are shifted in 1's to "ghost" the image but make it brighter
// 5/6/7: Make the red pixel its usual value and the green/blue values 0 (or make the
//        green its usual and the red/blue 0, or blue its usual and the red/green 0)
// 7/8/9: Make the red (or green or blue) the grayscale value and the other values 0
// 10: write a SwapNibbles function that swaps the nibbles of each color
// 11: rotate the red/green/blue components


void GrayscaleFormula(PIXEL* pixelPtr)
{
	BYTE gray = (BYTE)(pixelPtr->bBlu * 0.11 + pixelPtr->bGrn * 0.59
		+ pixelPtr->bRed * 0.3);

	pixelPtr->bBlu = gray;
	pixelPtr->bGrn = gray;
	pixelPtr->bRed = gray;
}


void Negative(PIXEL* pixelPtr)
{
	pixelPtr->bBlu = 255 - pixelPtr->bBlu; // Be careful with your math calculations
										   // that you do not overflow the pixel component
	pixelPtr->bGrn = ~pixelPtr->bGrn;
	pixelPtr->bRed = ~pixelPtr->bRed;
}

void GhostDarker(PIXEL* pixelPtr)
{
	pixelPtr->bBlu = pixelPtr->bBlu >> 1;
	pixelPtr->bGrn = pixelPtr->bGrn >> 1;
	pixelPtr->bRed = pixelPtr->bRed >> 1;

}

void GhostBrighter(PIXEL* pixelPtr)
{
	pixelPtr->bBlu = (pixelPtr->bBlu >> 2 | 0b11000000);
	pixelPtr->bGrn = (pixelPtr->bGrn >> 2 | 0b11000000);
	pixelPtr->bRed = (pixelPtr->bRed >> 2 | 0xC0);

}

void SwapNibbles(PIXEL* pixelPtr)
{
	pixelPtr->bBlu = (pixelPtr->bBlu >> 4) | (pixelPtr->bBlu << 4);
	pixelPtr->bGrn = (pixelPtr->bGrn>> 4) | (pixelPtr->bGrn << 4);
	pixelPtr->bRed = (pixelPtr->bRed >> 4) | (pixelPtr->bRed << 4);
}

// Two-pixel functions
void Blend(PIXEL* p1, PIXEL* p2)
{
	p1->bBlu = p1->bBlu / 2 + p2->bBlu / 2;
	p1->bGrn = p1->bGrn / 2 + p2->bGrn / 2;
	p1->bRed = p1->bRed / 2 + p2->bRed / 2;
	
}

// Write a function Hide that takes in two pixels and combines the top 4 bits (or top nibble)
// Of the first pixel with the top 4 bits of the second pixel, but the top 4 bits of the
// second pixel will become the bottom 4 bits of the resulting pixel
void Hide(PIXEL* p1, PIXEL* p2)
{
	p1->bBlu = (p1->bBlu & 0xF0) | (p2->bBlu >> 4);
	p1->bGrn= (p1->bGrn & 0xF0) | (p2->bGrn >> 4);
	p1->bRed = (p1->bRed & 0xF0) | (p2->bRed >> 4);
}

// Write a function Overwrite that will set 

void TestLoadWriteImage()
{
	FILE* infile = GetFile("Enter file to open: ", "rb");
	IMAGE img = { NULL, NULL };

	if (infile != NULL)
	{
		ReadImage(&img, infile);
		fclose(infile);
		if (img.bmHDR != NULL)
		{
			PrintHeader(img.bmHDR);

			// Manipulate the image...
			//ManipulateImage(&img, GrayscaleAverage);
			//ManipulateImage(&img, GrayscaleFormula);
			//ManipulateImage(&img, Negative);
			//ManipulateImage(&img, GhostDarker);
			//ManipulateImage(&img, GhostBrighter);
			ManipulateImage(&img, SwapNibbles);

			FILE* outfile = GetFile("Enter file to save to: ", "wb");
			if (outfile == NULL)
			{
				printf("Error opening file for writing: %s\n", strerror(errno));
			}
			else
			{
				// Manipulate the image
				WriteImage(&img, outfile);
				fclose(outfile);
			}

			FreeImage(&img);
		}
	}
	else
	{
		printf("The file did not open properly for reading: %s\n", strerror(errno));
	}
}

void TestTwoImages()
{
	FILE* infile1 = GetFile("Enter 1st file to open: ", "rb");
	FILE* infile2 = GetFile("Enter 2nd file to open: ", "rb");
	FILE* outfile = GetFile("Enter filename ot save: ", "wb");
	
	IMAGE img1 = { NULL, NULL };
	IMAGE img2 = { NULL, NULL };

	if (infile1 != NULL && infile2 != NULL && outfile != NULL)
	{
		// Read in the images
		ReadImage(&img1, infile1);
		ReadImage(&img2, infile2);
		// Could check for successful read...

		// Close our files
		fclose(infile1);
		fclose(infile2);

		// Manipulate the first image to combine it with the second image
		//ManipulateTwoImages(&img1, &img2, Blend);
		//ManipulateTwoImages(&img1, &img2, Hide);
		WriteImage(&img1, outfile);
		fclose(outfile);

		FreeImage(&img1);
		FreeImage(&img2);
	}
	else
	{
		printf("One of the files didn't open\n");
	}

}

void TestResizeCanvas()
{
	FILE* infile = GetFile("Enter file to open: ", "rb");
	IMAGE img1 = { NULL, NULL };
	ReadImage(&img1, infile);
	fclose(infile);

	IMAGE img2 = ResizeCanvas(&img1, 200, 200);
	FILE* outfile = GetFile("Enter file to save to: ", "wb");
	WriteImage(&img2, outfile);
	fclose(outfile);

	FreeImage(&img1);
	FreeImage(&img2);
}

void TestCrop()
{
	FILE* infile = GetFile("Enter file to open: ", "rb");
	IMAGE img1 = { NULL, NULL };
	ReadImage(&img1, infile);
	fclose(infile);

	IMAGE img2 = Crop(&img1, 10, 10, 10, 10);
	FILE* outfile = GetFile("Enter file to save to: ", "wb");
	WriteImage(&img2, outfile);
	fclose(outfile);

	FreeImage(&img1);
	FreeImage(&img2);
}

int main()
{
	//printf("Size of BITMAPHDR: %zu\n", sizeof(BITMAPHDR));
	//printf("Size of PIXEL: %zu\n", sizeof(PIXEL));

	//TestLoadWriteImage();
	//TestTwoImages();

	//TestResizeCanvas();
	TestCrop();

	return EXIT_SUCCESS;
}
