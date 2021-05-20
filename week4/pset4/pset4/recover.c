#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;

// function prototypes
long fsize_func(FILE *);
char * create_name(int);
void check_pointer(void *, char *);
int beginning_of_jpg(FILE *inptr);

int main(void)
{   
    
    // name of file we recover data from
    char *input_file = "card.raw";
    
    // open the file
    FILE* inptr = fopen(input_file, "r");
    
    // check pointer
    check_pointer(inptr, input_file);

	// compute card.raw file size
	long file_size = fsize_func(inptr);
	
	// file position indicator to input_file
	long p_position = 0;
	
    // number of images counter
    int nb_image = 0;
    
    // 
    int same_file = 0; 

	// name pointer
	char *name = NULL;
	
    // a buffer of 512 bytes
    BYTE buffer[512];
   
    // temp file output
    FILE* temp = NULL; 
    
    // until end of file is reached  
    while (p_position < file_size)
    {


        if (beginning_of_jpg(inptr))
        {
			
			// 
            fread(buffer, sizeof(buffer), 1, inptr);
            
			/** 
			 * free last image name if it exists
			 * create new image name 
			 *		AND
			 * increment number of images 
			 */ 
			if (name)
			{
				free(name);
				name = create_name(nb_image++);
			}
			else
			{
				name = create_name(nb_image++);
			}

            // close last file if it's still open
            if (temp != NULL)
            {
                fclose(temp);           
            }
     
            // open new file in write mode
            temp = fopen(name, "w");
            
            // new file with buffer
            fwrite(buffer, sizeof(buffer), 1, temp);
            
            same_file = 1;
        }
        
        // how ugly this is !
        else if (same_file)
        {
	        // fread 512 bytes chunks, so the 
	        fread(buffer, sizeof(buffer), 1, inptr);
	        
            // put jpg into temp
            fwrite(buffer, sizeof(buffer), 1, temp);            
        }
        else
        {
	        // fread 512 bytes chunks, so the 
	        fread(buffer, sizeof(buffer), 1, inptr);
        }
        
		p_position = ftell(inptr);
    }
  
	free(name);
	
    // close the file
    fclose(inptr);
    fclose(temp);

    // that's all folks
    return 0;
}

/**
 * compute a file size through its pointer
 */
long fsize_func(FILE * inptr)
{

	fseek(inptr, 0, SEEK_END);
	int f_size = ftell(inptr);
	fseek(inptr, 0, SEEK_SET);

	return f_size;
}

/**
 * Create names for the pictures we recovered
 * names are 0 indexed
 */
char * create_name(int nb_image)
{
	
	// malloc just enough space
	char *name = malloc(8 * sizeof(char));

	// check pointer mallocation	
	check_pointer(name, "pointer name");

	// create name this format : ###.jpg
	sprintf(name,"%.3i.jpg", nb_image);

	return name;
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

/**
 * find the beginning of a jpg file
 * through the jpg's Start Of Image proprety
 * returns a file position indicator
 */
int beginning_of_jpg(FILE *inptr)
{

		// create an array to store 4 bytes 
		// so we can compare it agains Sart Of Image
		BYTE tmp[4] = {0};
		for (int i = 0; i < 4; i++)
		{
			fread(&tmp[i], 1, 1, inptr);
		}
		
		// back 4 bytes
		fseek(inptr, ftell(inptr) - 4, SEEK_SET);

		// a as result in the right order
		// unsignend int to prevent from undefined behaviour in the left-shift operation
		// cf: https://github.com/nothings/stb/issues/152 third answer
		// Start Of Image
		unsigned int SOI = 0;
		
		for (int i = 0; i < 4; i++)
		{
			
			SOI += tmp[i];
			
			// don't move bytes the last time
			if(i == 3)
				break;
				
			// move left 8 bytes
			SOI = SOI << 8;
		}
	
		/**
		 * compare four_bytes against all possible values for a Start Of Image
		 * return 1 if a JPG signature was found 
		 * else return 0
		 */
		if (SOI >= 0xffd8ffe0 && SOI <= 0xffd8ffe9)
		{
			
			// new jpg found, return "true"
			return 1;
		}
		
		else
		{
			// no new jpg, return "false"
			return 0;
		}
		
}