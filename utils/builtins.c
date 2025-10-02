#include "shell.h"
#include <windows.h>

// External reference to current_dir from shell.c
extern char current_dir[MAX_PATH];

// Define the builtin arrays here (not in the header)
char *builtin_str[] = {
    "cd",
    "help",
    "exit",
    "ls",
};

int (*builtin_func[])(char **) = {
    &shell_cd,
    &shell_help,
    &shell_exit,
    &shell_ls,
};

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

int shell_ls(char **args)
{
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;

    char searchPath[MAX_PATH + 3]; // Extra space for \* and null terminator
    snprintf(searchPath, sizeof(searchPath), "%s\\*", current_dir);

    hFind = FindFirstFile(searchPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("ls: cannot access '%s': No such file or directory\n", current_dir);
        return 1;
    }

    do
    {
        const char *name = findFileData.cFileName;
        if (strcmp(name, ".") != 0 && strcmp(name, "..") != 0)
        {
            printf("%s\n", name);
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
    return 0;
}