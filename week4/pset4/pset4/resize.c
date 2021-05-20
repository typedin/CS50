#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

// function prototypes
BITMAPINFOHEADER new_BITMAPINFOHEADER(BITMAPINFOHEADER bi, int n);
BITMAPFILEHEADER new_BITMAPFILEHEADER(BITMAPFILEHEADER bf, DWORD biSizeImage);
int padding_func(LONG width);
void write_new_line(RGBTRIPLE *line_pxl,FILE *outptr, int newWidth, int origalWidth, int user_input);
void check_pointer(void *, char *);

int main(int argc, char* argv[])
{
 	// ensure proper usage
    if (argc != 4)
    {
        printf("Usage: resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

	// user input resize value
	int n = atoi(argv[1]);

	// validate user input
	if (n < 1 || n > 100)
	{
		fprintf(stderr, "ERROR ! n must be a positive integer less than or equal to 100.\n(Got %d)\n", n);
		return 4;
	}
	
    // open input file
    FILE* inptr = fopen(infile, "r");
    check_pointer(inptr, infile);

    // open output file
    FILE* outptr = fopen(outfile, "w");
    check_pointer(outptr, outfile);

	// read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

	// create new_BITMAP*HEADERs

	BITMAPINFOHEADER new_bi = new_BITMAPINFOHEADER(bi, n);
	BITMAPFILEHEADER new_bf = new_BITMAPFILEHEADER(bf, new_bi.biSizeImage);

    // write outfile's BITMAPFILEHEADER
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

	// write outfile's BITMAPINFOHEADER
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);


	// determine padding for scanlines
	int padding = padding_func(bi.biWidth);

	// create an "array" of RGBTRIPLE to store each TRIPLE in the scanline
	RGBTRIPLE *line_pxl = malloc(new_bi.biWidth * sizeof(RGBTRIPLE));
	check_pointer(line_pxl, "line_pxl");

	//	iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
		// iterate over pixels in scanline
		for (int j = 0; j < bi.biWidth; j++)
		{
			// read RGB triple from infile
			fread(&line_pxl[j], sizeof(RGBTRIPLE), 1, inptr);
		}

		// write RGB triple to outfile
		write_new_line(line_pxl, outptr, new_bi.biWidth, bi.biWidth, n);

		// skip over padding, if any
		fseek(inptr, padding, SEEK_CUR);
    }


	/**
	 *	fclose file(s) 
	 *  free mallocations
	 */

	// free line_pxl
	free(line_pxl);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks

    return 0;
}


BITMAPINFOHEADER new_BITMAPINFOHEADER(BITMAPINFOHEADER bi, int n)
{

	// assignment by copying
	BITMAPINFOHEADER new_bi = bi;
	
	// change only what is needed to be changed
	// multiply dimensions by n
	new_bi.biWidth = bi.biWidth * n;
	new_bi.biHeight = bi.biHeight * n;

	// new padding calculation
	int new_padding = padding_func(new_bi.biWidth);

	// new biSizeImage
	new_bi.biSizeImage = (new_bi.biWidth 
							* sizeof(RGBTRIPLE)
							+ new_padding)
							* abs(new_bi.biHeight);

	return new_bi;
}

BITMAPFILEHEADER new_BITMAPFILEHEADER(BITMAPFILEHEADER bf, DWORD  biSizeImage)
{
	// assignment by copying
	BITMAPFILEHEADER new_bf = bf;

	// change only what is needed to be changed
	new_bf.bfSize = biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER);

	return new_bf;
}

void write_new_line(RGBTRIPLE *line_pxl, FILE *outptr, int newWidth, int originalWidth, int n)
{
	
	for(int i = 0 ; i < n ; i++)
	{
		// iterate over the array of pixels
		for (int j = 0 ; j < originalWidth; j++)
		{
			// fwrite the same pixel n times to the outfile
			for(int k = 0 ; k < n ; k++)
			{
				fwrite(&line_pxl[j], sizeof(RGBTRIPLE), 1, outptr);
			}
		}

		// add padding
		for(int j = 0, padding = padding_func(newWidth) ; j < padding ; j++)
		{
			fputc(0x00, outptr);
		}
	}

}

/**
 * Padding calculation CS50 way
 * return int
 */
int padding_func(LONG width)
{
	return (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4 ;
}

/**
 * Check pointers, because I'm fed of typing the same thing over and over again
 * takes 2 arguments :
 * 1) the pointer itself
 * 2) the pointer name
 */
void check_pointer(void *pointer, char *pointer_name)
{

	// exit if pointer doesn't exist OR the size of malloc is negative
	if (pointer == NULL || pointer < 0)
	{

		fprintf(stderr, "unable to open %s\n", pointer_name);
		free(pointer);
		exit (1);
	}
}