#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{

//	destination[0] = '\0';

	const char *source1 = "first";
	char *source2 = "second";
	
	char *destination = malloc((strlen(source1) + strlen(source2) + sizeof('\0')) * sizeof(char));

	strcat(destination, source1);
	
	printf("%s\n", destination);

	strcat(destination, source2);
	
	printf("%s\n", destination);
	
	printf("%c\n", destination[strlen(source1) + strlen(source2) + 1]);
	free(destination);

	return 0;
}
