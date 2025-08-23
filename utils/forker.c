#include "../include/forker.h"

void fork_and_execute(char** args) {
    pid_t pid = fork();
    int child_status;

    // parent process
    if (pid) { 
        pid = wait(&child_status); 
    } 

    // child process
    else {
        if(execvp(args[0], args)) {
            puts(strerror(errno));
            exit(127);
        }
    }
}