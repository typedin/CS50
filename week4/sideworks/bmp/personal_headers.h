#ifndef INCLUDED
	#include "resize.c"
	#include "bmp.h"
#endif /* INCLUDED*/

void update_HEADERS(BITMAPFILEHEADER *, BITMAPINFOHEADER *, int n);

void compute_array(RGBTRIPLE *triple_array, int offset, FILE *inptr, int factor_by_size);

void populate_new_line(RGBTRIPLE *triple, RGBTRIPLE *line_pxl, int offset);

DWORD write_new_line(RGBTRIPLE *line_pxl,FILE *outptr, int newWidth, int origalWidth, int user_input);

RGBTRIPLE** create_line_pxl(int n);

void free_pointers(RGBTRIPLE *line_pxl, int n);

void print_info_BMFILEH(BITMAPFILEHEADER p_BMFH);

void print_info_BMINFOH(BITMAPINFOHEADER p_BMIH);

