#include "shell.h"
#include <windows.h>

// External reference to current_dir from shell.c
extern char current_dir[MAX_PATH];

// Define the builtin arrays here (not in the header)
char *builtin_str[] = {
    "cd",
    "help",
    "exit"};

int (*builtin_func[])(char **) = {
    &shell_cd,
    &shell_help,
    &shell_exit};

int shell_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

int shell_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "shell: expected argument to \"cd\"\n");
    }
    else
    {
        if (SetCurrentDirectory(args[1]) == 0)
        {
            printf("cd: cannot change directory to '%s'\n", args[1]);
        }
        else
        {
            GetCurrentDirectory(MAX_PATH, current_dir);
        }
    }
    return 0;
}

int shell_help(char **args)
{
    printf("Sea Shell - A simple Windows shell\n");
    printf("Built-in commands:\n");

    for (int i = 0; i < shell_num_builtins(); i++)
    {
        printf("  %s\n", builtin_str[i]);
    }

    printf("\nUse 'exit' to quit the shell.\n");
    printf("Other commands will be executed as external programs.\n");
    return 0;
}

int shell_exit(char **args)
{
    return 1; // Return 1 to exit the shell loop
}