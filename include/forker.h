#ifndef FORKER_H
#define FORKER_H

#include <sys/types.h>
#include <errno.h>

void fork_and_execute(char** args);

#endif