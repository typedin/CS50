#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{	
	//
	const char *request_target = "/home/antoine/workspace/CS50/week7/sidewok/tests/hello.php";
	
	char *abs_path = malloc(strlen(request_target) + 1);
	
	abs_path[0] = '\0';
	strcpy(abs_path, request_target);
	abs_path = strtok(abs_path, "?");
	
	printf("abs_path: %s\n", abs_path);
	
	
	
	
	
	
	
	char *query = malloc(strlen(request_target) + 1);
	
	query[0] = '\0';
	strcpy(query, request_target);
	
	printf("query before the mess: %s\n", query);
	
	
	if (strstr(query, "?"))
	{
		query = strchr(query, 63) + 1;

	}
	else
	{
		query[0] = '\0';
	}

	printf("query after the mess: %s\n", query);
	
	return 0;
}
