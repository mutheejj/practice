#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;
int big_print(const char *format, ...);
ssize_t letaline(char **rodman, size_t *q, FILE *lineup);

#define MAX_INPUT_LINE 1024
#define MAX_ARGS 1000



#endif
