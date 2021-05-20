#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 65535

int main()
{
	char buffer[MAX];

	int fd_null = open("/dev/null", 'r');

	printf("%d\n", fd_null);


	int fd_zero = open("/dev/zero", 'r');

	printf("%d\n", fd_zero);


	int fd_tty = open("/dev/tty", 'r');

	printf("%d\n", fd_tty);

	char *message = "message";
	int x= 5;
	int *length = &x;
	int bytes = 12;
	int offset = 4;

	char* haystack = *message + *length - bytes - offset;

	return 0;
}
