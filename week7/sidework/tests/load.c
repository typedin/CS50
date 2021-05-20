#define _GNU_SOURCE

// header files
#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// types
typedef char BYTE;

/**
 * I was about to compute the size of a file with fseek but:
 *
 * https://www.securecoding.cert.org/confluence/display/c/FIO19-C.+Do+not+use+fseek%28%29+and+ftell%28%29+to+compute+the+size+of+a+regular+file
 * https://www.lemoda.net/c/get-file-size/
 * https://www.quora.com/In-Linux-how-is-a-file-descriptor-and-a-FILE*-converted-back-and-forth
 * more info here : man fstat
 * all the includes were here, because the staff uses "struct stat ""
 */
/**
 * Loads a file into memory dynamically allocated on heap.
 * Stores address thereof in *content and length thereof in *length.
 */
bool load(FILE* file, BYTE** content, size_t* length)
{
	
	// get the length of file a "secure way"
    struct stat s_file;
    
    if (fstat(fileno(file), &s_file) != 0)
	{
		fprintf(stderr, "fstat failed : %s.\n", strerror(errno));
		return false;
	}
	
    *length = s_file.st_size;    

    // allocate enough memory for content
    *content = malloc(sizeof(BYTE) * *length);
    
    // copy the file into content
    fread(*content, *length, 1, file);

    return true;

}

int main()
{
	
	FILE *fp = fopen("index.php", "r");
	// not mallocated
	char *content;
	size_t length;
	
	load(fp, &content, &length);
	
	printf("length %ld\n", length);
	
	free(content);
	fclose(fp);
	return 0;
}
