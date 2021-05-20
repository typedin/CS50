#ifndef INCLUDED
	#include "resize.c"
	#include "bmp.h"
	#include "perso_headers.c"
#endif /* INCLUDED*/

/*
 *
**/
BITMAPINFOHEADER new_BITMAPINFOHEADER(BITMAPINFOHEADER *bi, int n)
{

	BITMAPINFOHEADER new_bi = *bi;

	new_bi.biWidth = bi->biWidth * n;
	new_bi.biHeight = bi->biHeight * n;
	new_bi.biSizeImage = bi->biSizeImage * n;

	return new_bi;
}

BITMAPFILEHEADER new_BITMAPFILEHEADER(BITMAPFILEHEADER *bf)
{
	BITMAPFILEHEADER new_bf = *bf;
	
	return new_bf;
}

void populate_new_line(RGBTRIPLE *triple, RGBTRIPLE *line_pxl, int i)
{
	line_pxl[i] = *triple;
}

DWORD write_new_line(RGBTRIPLE *line_pxl, FILE *outptr, int newWidth, int origalWidth, int user_input)
{
	// padding calculation CS50's version
	int padding = (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4;

	DWORD nb_bytes = 0;

	//
	for(int i = 0 ; i < user_input ; i++)
	{
		// iterate over the array of pixels
		for (int j = 0 ; j < origalWidth ; j++)
		{
			// fwrite the same pixel user_in's times to the outfile
			for(int k = 0; k < user_input; k++)
			{
				fwrite(&line_pxl[j], sizeof(RGBTRIPLE), 1, outptr);
				nb_bytes += sizeof(RGBTRIPLE);
			}
		}

		// add padding
		for(int j = 0; j < padding; j++)
		{
			fputc(0x00, outptr);
			nb_bytes += sizeof(0x00);
		}
	}

	return nb_bytes;
}

