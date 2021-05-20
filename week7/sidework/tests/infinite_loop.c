#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


// file descriptor for sockets
int cfd = -1, sfd = -1;

int main()
{
	char *path = NULL;
	char *message = NULL;
	int length = 0;

	while (true)
	{
		// free last path, if any
		if (path != NULL)
		{
			free(path);
			path = NULL;
		}

		// free last message, if any
		if (message != NULL)
		{
			free(message);
			message = NULL;
		}
		length = 0;

		// close last client's socket, if any
		if (cfd != -1)
		{
			close(cfd);
			cfd = -1;
		}

		// check for control-c
		if (signaled)
		{
			stop();
		}

		// check whether client has connected
		if (connected())
		{
			// check for request
			if (request(&message, &length))
			{
			// extract message's request-line
			// http://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html
			const char* haystack = message;
			const char* needle = strstr(haystack, "\r\n");
			if (needle == NULL)
			{
				error(500);
				continue;
			}
			char line[needle - haystack + 2 + 1];
			strncpy(line, haystack, needle - haystack + 2);
			line[needle - haystack + 2] = '\0';

			// log request-line
			printf("%s", line);

			// parse request-line
			char abs_path[LimitRequestLine + 1];
			char query[LimitRequestLine + 1];
			if (parse(line, abs_path, query))
			{
				// URL-decode absolute-path
				char* p = urldecode(abs_path);
				if (p == NULL)
				{
				    error(500);
				    continue;
				}

				// resolve absolute-path to local path
				path = malloc(strlen(root) + strlen(p) + 1);
				if (path == NULL)
				{
				    error(500);
				    continue;
				}
				strcpy(path, root);
				strcat(path, p);
				free(p);

				// ensure path exists
				if (access(path, F_OK) == -1)
				{
				    error(404);
				    continue;
				}

				// if path to directory
				struct stat sb;
				if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
				{
				    // redirect from absolute-path to absolute-path/
				    if (abs_path[strlen(abs_path) - 1] != '/')
				    {
				        char uri[strlen(abs_path) + 1 + 1];
				        strcpy(uri, abs_path);
				        strcat(uri, "/");
				        redirect(uri);
				        continue;
				    }

				    // use path/index.php or path/index.html, if present, instead of directory's path
				    char* index = indexes(path);
				    if (index != NULL)
				    {
				        free(path);
				        path = index;
				    }

				    // list contents of directory
				    else
				    {
				        list(path);
				        continue;
				    }
				}

				// look up MIME type for file at path
				const char* type = lookup(path);
				if (type == NULL)
				{
				    error(501);
				    continue;
				}

				// interpret PHP script at path
				if (strcasecmp("text/x-php", type) == 0)
				{
				    interpret(path, query);
				}

				// transfer file at path
				else
				{
				    transfer(path, type);
				}
			}
		}
	}

    return 0;
}
