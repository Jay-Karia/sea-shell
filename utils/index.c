#include <stdio.h>
#include <stdlib.h>

#include "../include/sea-shell.h"

void shell_loop(void)
{
	char* line;
	char** args;
	int status;

	do {
		printf("%s\n", PROMPT);
		line = read_line();
		args = split_line(line);
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
		} else {
			buffer[position] = c;
		}
		position++;
	}

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