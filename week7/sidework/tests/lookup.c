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
 * Returns MIME type for supported extensions, else NULL.
 */
const char* lookup(const char* path)
{
    // TODO
    struct valid_extensions
    {
    	const char *name;
    	const char *mime_type;

    };
    
    struct valid_extensions valid_ext_arr[] =
    {
		{"css", "text/css"},
		{"html", "text/html"},
		{"gif", "image/gif"},
		{"ico", "image/x-icon"},
		{"jpg", "image/jpeg"},
		{"js", "text/javascript"},
		{"php", "text/php"},
		{"png", "image/png"}
    };
    
    // The strchr() function returns a pointer to the first occurrence of the character c in the string s.
    // if it's a pointer, then we can do some pointer arithmetic !!!
    const char *extension = strchr(path, '.') + 1;

    
    if(extension == NULL)
    {
    	return NULL;
    }
    
    for(int i = 0 ; i < 8 ; i++)
    {
    	if(strcasecmp(extension, valid_ext_arr[i].name) == 0)
    	{
    		return valid_ext_arr[i].mime_type;
    	}
    }
    
    // no match found, return NULL
    return NULL;
}


int main()
{
	
	const char *filename = "text.gif";
	
	const char *mime_type= lookup(filename);
	
	printf("%s\n", mime_type);
	
	return 0;
}
