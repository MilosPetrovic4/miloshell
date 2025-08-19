
#include <unistd.h>
#include <sys/types.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#define BUFFER_SIZE 1024
#define MAX_ARGS 64

// Function to parse the input buffer into arguments
void parse_input(char** args, char* input) {

    int i = 0;
    char *token = strtok(input, " \t\n");

    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }

    args[i] = NULL;
}

// A simple shell implementation that forks a child process to execute commands
int main(int argc, char* argv[]) {

    char buffer[BUFFER_SIZE];
    char *args[MAX_ARGS];
    int child_status;
    pid_t pid;

    while(1) {

        printf("$");
        fgets(buffer, BUFFER_SIZE, stdin);
        parse_input(args, buffer);

        // Skip empty input
        if (args[0] == NULL) {
            continue;
        }

        pid = fork();

        // parent process
        if (pid){
            printf("Waiting for child (%d)\n", pid);
            pid = wait(&child_status);
            printf("Child (%d) finished\n", pid);
        } 
        // child process
        else {
            if(execvp(args[0], args)) {
                puts(strerror(errno));
                exit(127);
            }
        }

    }
    return 0;
}