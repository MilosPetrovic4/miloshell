#ifndef BCOMPILE_H
#define BCOMPILE_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

extern const char *GCC_PATH;
extern const char *GCC_WALL_FLAG;
extern const char *GCC_WEXTRA_FLAG;
extern const char *GCC_WERROR_FLAG;
extern const char *GCC_OUTPUT_FLAG;
extern const int GCC_REQ_ARG_COUNT;

int basic_gcc_compile(char** args);

#endif