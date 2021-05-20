#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


/**
 * OK = 0
 * NOT_OK = -1
 * F_OK : "file exists"
 * R_OK : "read ok"
 * W_OK : "write ok"
 * X_OK : "executable ok"
 */

typedef struct _file_permission
{
	char *path;
	int exist;
	int read;
	int write;
	int executable;
}
file_permission;

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("USAGE: ./access path_to_file");
		return 1;
	}

	file_permission *p_file = malloc(sizeof(file_permission));
	p_file->path = malloc(strlen(argv[1])*(sizeof(char)) + 1);

	strcpy(p_file->path, argv[1]);

	printf("Checking this : %s\n", p_file->path);

	if((p_file->exist = access(p_file->path,F_OK)) != 0)
	{
		printf("File doesn't exist\n");
		// could return errno here
		return 1;
	}

	p_file->read = access(p_file->path,R_OK);
	p_file->write = access(p_file->path,W_OK);
	p_file->executable = access(p_file->path,X_OK);

	// name r w x
	printf("%s %c%c%c\n", p_file->path,
		   !p_file->read? 'r':'_',
		   !p_file->write? 'w':'_',
		   !p_file->executable? 'x':'_');

	free(p_file->path);
	free(p_file);

	return 0;
}
