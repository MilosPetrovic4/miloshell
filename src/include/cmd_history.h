#ifndef CMD_HISTORY_H
#define CMD_HISTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const int MAX_HISTORY;
extern int history_count;
extern int history_index;

int add_history(const char* command);
const char *get_older_history();
const char *get_newer_history();
void reset_history_nav();
void reset_history_index();
void free_history();

#endif