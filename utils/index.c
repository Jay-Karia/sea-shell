#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../include/sea-shell.h"

void shell_loop(void)
{
	int status;

	do {
		printf("%s", PROMPT);
		char* line = read_line();
		char** args = tokenize(line);
		status = execute(args);

		free(line);
		free(args);
	} while (status);
}

char* read_line(void)
{
	int buffer_size = LINE_BUFFER_SIZE;
	int position = 0;

	// Create a buffer to hold the line
	char* buffer = malloc(sizeof(char) * buffer_size);

	if (!buffer) {
		fprintf(stderr, "sea-shell: allocation error\n");
		exit(EXIT_FAILURE);
	}

	// Read characters until we hit EOF or newline
	int c;
	while (1)
	{
		c = getchar();

		if (c == EOF || c == '\n') {
			buffer[position] = '\0';
			return buffer;
		}
		else {
			buffer[position] = c;
		}
		position++;

		// If buffer is exceeded, reallocate
		if (position >= buffer_size) {
			buffer_size += LINE_BUFFER_SIZE;
			buffer = realloc(buffer, buffer_size);
			if (!buffer) {
				fprintf(stderr, "sea-shell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

char** tokenize(char* line)
{
	int buffer_size = TOKEN_BUFFER_SIZE, position = 0;
	char** token_buffer = malloc(buffer_size * sizeof(char*));
	char* token;

	if (!token_buffer) {
		fprintf(stderr, "sea-shell: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOKEN_DELIMITERS);
	while (token != NULL) {
		token_buffer[position] = token;
		position++;
		if (position >= buffer_size) {
			buffer_size += TOKEN_BUFFER_SIZE;
			token_buffer = realloc(token_buffer, buffer_size * sizeof(char*));
			if (!token_buffer) {
				fprintf(stderr, "sea-shell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOKEN_DELIMITERS);
	}

	token_buffer[position] = NULL;
	return token_buffer;
}

int sea_shell_launch(char** args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("sea-shell");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("sea-shell");
	}
	else
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int execute(char** args)
{
	if (args == NULL || args[0] == NULL) {
		return 1;
	}
	return sea_shell_launch(args);
}