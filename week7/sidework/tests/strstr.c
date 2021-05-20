#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{	
	//
	const char *line = "GET /a/long/path/here HTTPvers\r\n";

	// create 3 milestones, one for each substring
	int ms1 = strchr(line, ' ') - line;

	// passing the substring strarting at ms1 + 1
	// looking for another SP
	int ms2 = strchr(&line[ms1 + 1], ' ') - line;
	
	// assuming the line we're passed is correctly formated...
	// passing a substring is unnecessary, anyway...
	int ms3 = strchr(&line[ms2 + 1], '\r') - line;
	
	// compute each new string size
	size_t methode_size = ms1 + 1;
	size_t abs_path_size = ms2 - ms1;
	size_t http_v_size = ms3 - ms2;

//	Method
	char *method = malloc(sizeof(char) * methode_size);
	if(method == NULL)
		return 1;
		
	method[0] = '\0';
	strncpy(method, line, methode_size - 1);
	method[methode_size] = '\0';
	printf("%s\n", method);

	
//	Abs_path	
	char *abs_path = malloc(sizeof(char) * abs_path_size);
	if(abs_path == NULL)
		return 1;

	abs_path[0] = '\0';
	strncpy(abs_path, &line[ms1+1], abs_path_size - 1);
	abs_path[abs_path_size] = '\0';
	printf("%s\n", abs_path);

// http_v
	char *http_v = malloc(sizeof(char) * http_v_size);
	if(http_v == NULL)
		return 1;

	http_v[0] = '\0';
	strncpy(http_v, &line[ms2 +1], http_v_size - 1);
	http_v[http_v_size] = '\0';
	printf("%s\n", http_v);

int i = strcmp("essai", "essai");
printf("%d\n", i);
	return 0;
}























