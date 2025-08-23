#include "../include/bcompile.h"
#include "../include/forker.h"

const char *GCC_PATH = "/usr/bin/gcc";
const char *GCC_WALL_FLAG = "-Wall";
const char *GCC_WEXTRA_FLAG = "-Wextra";
const char *GCC_OUTPUT_FLAG = "-o";
const int GCC_REQ_ARG_COUNT = 5;

int basic_gcc_compile(char** args) {

    if(args[1] == NULL) {
        fprintf(stderr, "Usage: bcompile <source_files>\n");
        exit(1);
    }

    char* exec_name = strdup(args[1]);
    char* dot = strrchr(exec_name, '.');

    if (dot != NULL && strcmp(dot, ".c") == 0) {
        *dot = '\0';
    }

    // count src files
    int i = 1;
    while (args[i] != NULL) i++;
    int source_count = i - 1;

    // prepare argument array
    int max_args = GCC_REQ_ARG_COUNT + source_count;
    char *gcc_args[max_args];

    int j = 0;
    gcc_args[j++] = (char *)GCC_PATH;
    gcc_args[j++] = (char *)GCC_OUTPUT_FLAG;
    gcc_args[j++] = exec_name;

    // source files
    for (int k = 1; k <= source_count; ++k) {
        gcc_args[j++] = args[k];
    }

    // flags
    gcc_args[j++] = (char *)GCC_WALL_FLAG;
    gcc_args[j++] = (char *)GCC_WEXTRA_FLAG;
    gcc_args[j] = NULL;

    fork_and_execute(gcc_args);
    return 0;
}