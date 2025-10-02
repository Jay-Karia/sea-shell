#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROMPT "~> "

enum {
	input_buffer_size = 1024,
	tokens_buffer_size = 64,
};

void shell_loop(void);
int execute_command(char** args);
char** parse_input(char* input);

#endif