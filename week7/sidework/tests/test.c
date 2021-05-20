#include <stdio.h>
#include <string.h>

int main()
{


	// strstr "cuts" the haystack string, at the first occurence of the string
	// we're searching.
	// eg: strstr("this is a message...", "message") == "message...")

	const char* haystack = "Method SP Request-URI SP HTTP-Version\r\nmessage";
	// the following "cuts" haystack after the first occurence of "\r\n"
	const char* needle = strstr(haystack, "\r\n");

	printf("%s(%ld)\n", haystack, strlen(haystack));
	printf("%s (%ld)\n", needle, strlen(needle));

	char line[needle - haystack + 2 + 1];

	int n = needle - haystack;

	printf("line_size: %d\n", n);

	long int_needle = (long)needle;
	long int_haystack = (long)haystack;

	if (needle == NULL)
	{
		printf("Error 500\n");
	}
	else
	{
		//char *strncpy(char *dest, const char *src, size_t n);
		strncpy(line, haystack, needle - haystack);
		printf("character: %c\n", line[n]);
		line[needle - haystack + 2] = '\0';
		printf("character: %c\n", line[n+2]);
	}

	// print some greenish text:
	printf("\033[32m");
	printf("line: %s\n", line);

 	// redish
    printf("\033[33m");
	printf("line: %s\n", line);

	// back to normal
	printf("\033[39m");
	printf("line: %s\n", line);

	char *tchoupi1 = "Antoine";
	char *tchoupi2 = "Myriam";
	char *what = "aime vraiment beaucoup";

	int nb_char = printf("%s %s %s\n", tchoupi1, what, tchoupi2);

	printf("%d\n", nb_char);



	return 0;
}
