#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char* indexes(const char* path)
{

    // compute the size of the full path plus the string "index."
	size_t base_size = strlen(path) + strlen("index.");

	// malloc a new "string" in order to create a full path for the index
	// this new string will be the size of the path + the size of "index.php" + '\0'
	char *index_path = malloc(sizeof(char) * (base_size + sizeof("php")) + 1);

	// check for error in malloc()
	if (index_path == NULL)
	{
		// maybe perror() should go into the infinite while loop in main
		// perror();
		return NULL;
	}	
	
	
	// avoid error in Valgrind
	// Conditional jump or move depends on uninitialised value(s)
	index_path[0] = '\0';	
	
	// create the full path string	
	strcat(index_path, path);
	strcat(index_path, "index.php");
		
	// check if index.php exists in the given path
	if(access(index_path, F_OK) == 0)
	{
		// file exists
		return index_path;
	}
	// check if index.html exist in the given path
	else
	{
		
		index_path = realloc(index_path, (sizeof(char) * (base_size + sizeof("html")) + 1));
		// cut only where needed
		index_path[base_size] = '\0';
		
		// recreate the full_path string by appending the extension
		strcat(index_path, "html");
			
		if(access(index_path, F_OK) == 0)
		{
			// file exists
			return index_path;
		}
	}
	
	// file doesn't exist
	free(index_path);
	
    return NULL;
}


int main()
{

	char *full_path = indexes("/home/antoine/workspace/CS50/week7/sidework/tests/");
	
	if (full_path != NULL)
		printf("%s\n", full_path);
	else
		printf("not found\n");
	
		
	free(full_path);
	
	return 0;
}
