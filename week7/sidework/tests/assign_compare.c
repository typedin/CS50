#include <stdio.h>
#include <string.h>

int main()
{
	int j = 0;
	char *string = "testkk";
	if(j = (strchr(string, '?') - string))
		printf("ok");
		
		printf("%d\n", j);
	return 0;
}
