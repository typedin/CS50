#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char **argv)
{

	const char *usage = "Usage: server [-p port] /path/to/root";

	int opt;
	int port = 8080;

		// the getopt is used to break up (parse) options in command lines
		// for easy parsing by shell procedures
		//
		// When getopt encounters an unknown option character or an option with a
		// missing required argument, it stores that option character in this
		// variable. You can use this for providing your own diagnostic messages.
    while ((opt = getopt(argc, argv, "hp:")) != -1)
    {
				printf("opt: %d \n", opt);
				switch (opt)
				{
					// -h
					case 'h':
						printf("default: %s\n", usage);
						return 0;

					case 'p':
						port = atoi(optarg);
					break;

					default:
						printf("using default port (%d)\n", port);
						break;
				}
    }

		printf("port: %d\n", port);
	return 0;
}
