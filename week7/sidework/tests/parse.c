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
bool parse(const char* line, char* abs_path, char* query)
{
    
    char *local_line = malloc(strlen(line) + 1);
    strcpy(local_line, line);
    
	// create 3 milestones, one for each substring
	// so we can access the string 
	int ms1 = strchr(line, ' ') - line;

	// passing the substring strarting at ms1 + 1
	// looking for another SP
	int ms2 = strchr(&line[ms1 + 1], ' ') - line;
	
	// assuming the line we're passed is correctly formated...
	// passing a substring is unnecessary, anyway...
	int ms3 = strchr(&line[ms2 + 1], '\r') - line;
	
	// compute the size of each new bub strings
	size_t methode_size = ms1 + 1;
	size_t request_target_size = ms2 - ms1;
	size_t http_v_size = ms3 - ms2;


//	Method
	char *method = malloc(sizeof(char) * methode_size);
	if(method == NULL)
		return false;
		
	method[0] = '\0';
	strncpy(method, line, methode_size - 1);
	method[methode_size - 1] = '\0';
// DEBUG	
	printf("%s\n", method);
		
//	request_target	
	char *request_target = malloc(sizeof(char) * request_target_size);
	if(abs_path == NULL)
		return false;

	request_target[0] = '\0';
	strncpy(abs_path, &line[ms1 + 1], request_target_size - 1);
	request_target[request_target_size - 1] = '\0';
// DEBUG
	printf("%s\n", request_target);
// QUERY
	*query 
// http_v
	char *http_v = malloc(sizeof(char) * http_v_size);
	if(http_v == NULL)
		return false;

	http_v[0] = '\0';
	strncpy(http_v, &line[ms2 + 1], http_v_size - 1);
	http_v[http_v_size - 1] = '\0';
// DEBUG
	printf("%s\n", http_v);

	// the easy ones
	if(strcmp(method, "GET") != 0)
	{
		error(405);
		return false;
	}
	if(strcmp(http_v, "HTTP/1.1") != 0)
	{
		error(505);
		return false;
	}

// check request_target
	// / is 47 in ASCII
	if(request_target[0] != 47)
	{
		error(501);
		return false;
	}
	// ' is 39 in ASCII
	else if(strchr(request_target, 39) != 0)
	{
		error(400);
		return false;
	}
	// abs_path is ok, return a consistant query
	else
	{	
		// include null character
		query = malloc(strlen(abs_path) + 1);
		if(query == NULL)
		{
			error(500);
			return false;
		}
		if (strstr(query, "?"))
		{
			query = strchr(query, 63) + 1;
		}
		else
		{
			query[0] = '\0';
		}
	}
	
    error(501);
    return false;
}


int main()
{
	
	const char *filename = "text.gif";
	
	const char *mime_type= lookup(filename);
	
	printf("%s\n", mime_type);
	
	return 0;
}
