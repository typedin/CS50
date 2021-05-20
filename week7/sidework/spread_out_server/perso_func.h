/**
 * perso_func.h
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Declares a all functions' functionality.
 */

#ifndef PERSO_FUNC_H
#define PERSO_FUNC_H
#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>



// prototypes

char* indexes(const char* path);
bool load(FILE* file, BYTE** content, size_t* length);
const char* lookup(const char* path);
bool parse(const char* line, char* path, char* query);

#endif // PERSO_FUNC_H
