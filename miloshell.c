#include <unistd.h>
#include <sys/types.h>
#include <termios.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#include "include/cd.h"
#include "include/bcompile.h"
#include "include/utils.h"
#include "include/cmd_history.h"
#include "include/forker.h"

#define MAX_ARGS 64
#define BUFFER_SIZE 1024

// Function to parse the input buffer into arguments
void parse_input(char** args, char* input) {

    int i = 0;
    char *token = strtok(input, STR_TOKEN_DELIM);

    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, STR_TOKEN_DELIM);
    }

    args[i] = NULL;
}

// Shell entry point, forks current process to execute user's commands
int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    char buffer[BUFFER_SIZE];
    char *args[MAX_ARGS];

    struct termios original_term;

    enable_raw_mode(&original_term);

    while(1) {

        printf("$");
        fflush(stdout);

        int buf_pos = 0;
        memset(buffer, 0, BUFFER_SIZE);  // Clear buffer, set to zeros
        reset_history_index();

        while (1) {
            char c;
            if (read(STDIN_FILENO, &c, 1) != 1) continue;

            if (c == '\n') {
                buffer[buf_pos] = '\0';
                printf("\n");
                break;
            } else if (c == BACKSPACE_KEY) {
                fflush(stdout);
                if (buf_pos > 0) {
                    buf_pos--;
                    buffer[buf_pos] = '\0';
                    printf("\b \b");
                    fflush(stdout);
                }
            } else if (c == ESCAPE_CHAR) {
                char seq[2];
                if (read(STDIN_FILENO, &seq[0], 1) != 1) continue;
                if (read(STDIN_FILENO, &seq[1], 1) != 1) continue;

                if (seq[0] == '[') {
                    const char *hist_cmd = NULL;

                    // up arrow
                    if (seq[1] == UP_ARROW_KEY) {
                        hist_cmd = get_older_history();
                    } 
                    
                    // down arrow
                    else if (seq[1] == DOWN_ARROW_KEY) {
                        hist_cmd = get_newer_history();
                    }

                    if (hist_cmd) {
                        printf(CLEAR_LINE "$%s", hist_cmd); // clear line and print command
                        fflush(stdout);
                        strncpy(buffer, hist_cmd, BUFFER_SIZE - 1);
                        buffer[BUFFER_SIZE - 1] = '\0';
                        buf_pos = strlen(buffer);
                    }
                }
            } else if (c < 32 || c > 126) {
                // Ignore control characters except for backspace and up down arrows
                continue;
            }
            else {
                if (buf_pos < BUFFER_SIZE - 1) {
                    buffer[buf_pos++] = c;
                    write(STDOUT_FILENO, &c, 1);
                    fflush(stdout);
                }
            }
        }

        if (buffer[0] == '\0') {
            continue;
        }

        add_history(buffer);
        parse_input(args, buffer);

        if (strcmp(args[0], "cd") == 0) {
            change_dir(args[1]);
            continue;
        }

        if (strcmp(args[0], "bcompile") == 0) {
            basic_gcc_compile(args);
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            exit(0);
        }

        fork_and_execute(args);
    }
    disable_raw_mode(&original_term); 
    return 0;
}