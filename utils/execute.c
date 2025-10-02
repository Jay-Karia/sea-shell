#include "shell.h"

int execute_command(char** args)
{
    if (args) {
        for (int i = 0; args[i] != NULL; ++i) {
            printf("Arg[%d]: %s\n", i, args[i]);
        }
    }
    else {
        printf("No command entered.\n");
    }
    return 0;
}