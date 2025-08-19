#include "change_directory.h"

int change_dir(const char* path) {

    if (chdir(path) != 0) {
        perror("chdir failed");
        return -1;
    } 
    
    return 0;
}