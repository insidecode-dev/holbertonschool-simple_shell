#ifndef __FILE_NAME__
#define __FILE_NAME__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdint.h>

extern char **environ;

void runcommandline(char *);
int findpath(char *, char *);

#endif
