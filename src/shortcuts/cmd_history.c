#include "../include/cmd_history.h"

#define MAX_HISTORY 100

static char* cmd_history[MAX_HISTORY];
int history_count = 0;
int history_index = 0;

/**
 * Adds a command to the history.
 * Returns 0 on success, -1 if history is full.
 */
int add_history(const char* command) {
    if (history_count < MAX_HISTORY) {
        cmd_history[history_count++] = strdup(command);
        history_index = history_count;
        return 0;
    } else {
        return -1;
    }
}

/**
 * Retrieves the previous command in history.
 * If at the beginning of history, returns NULL. Up Arrow key
 */
const char *get_older_history() {
    if (history_index > 0) {
        return cmd_history[--history_index];
    } else if (history_index == 0) {
        return cmd_history[history_index];
    }
    return NULL;
}

/**
 * Retrieves the next command in history.
 * If at the end of history, returns the last command. Down Arrow key
 */
const char *get_newer_history() {
    if (history_index < history_count - 1) {
        return cmd_history[++history_index];
    } else if (history_index == history_count - 1) {
        return cmd_history[history_index];
    }
    return NULL;
}

/**
 * Resets the history count and index.
 */
void reset_history_nav() {

    history_count = 0;
    history_index = 0;
}

void reset_history_index() {
    history_index = history_count;
}

void free_history() {
    for (int i = 0; i < history_count; ++i) {
        free(cmd_history[i]);
    }
}

