#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_info(char * string, char *name)
{
	// is_null terminated
	
	int i = 0;
	while(1)
	{
		if(string[i++] == '\0')
		{
			printf("%s is null terminated at %d\n", name, i);
			break;
		}
	}
		
	printf("strlen of %s: %d\n", name, strlen(string));
	printf("content of %s: %s\n", name, string);	
	
	return;
}

int main()
{

	//	/!\ returns the number of characters (actually the number of bytes)
	// excluding the '\0'
	
	char *destination = malloc(16 * sizeof(char));

	char *source = "1234";

	
	print_info(destination,"destination");
	print_info(source, "source");

	strcpy(destination, source);
	
	print_info(destination,"destination");
	print_info(source, "source");
	
	free(destination);
	return 0;
}
