#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "builtins.h"

#define PROMPT "~> "
#define DELIMITERS " \t\r\n\a"

// External declaration of current directory
extern char current_dir[MAX_PATH];

void shell_loop(void);
int execute_command(char** args);
char** parse_input(char* input);
int launch_shell(char **args);

#endif