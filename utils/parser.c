#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

char** parse_input(char* input)
{
	size_t bufsize = 64;
	size_t position = 0;
	char** tokens = malloc(bufsize * sizeof(char*));

	if (!tokens) {
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	char* ptr = input;
	while (*ptr) {
		// Skip whitespace
		while (*ptr && strchr(" \t\r\n", *ptr)) ptr++;

		if (*ptr == '\"') {
			ptr++;
			char* start = ptr;
			while (*ptr && *ptr != '\"') ptr++;
			size_t len = ptr - start;
			char* token = malloc(len + 1);
			strncpy_s(token, len + 1, start, len);
			token[len] = '\0';
			tokens[position++] = token;
			if (*ptr == '\"') ptr++;
		}
		else if (*ptr) {
			char* start = ptr;
			while (*ptr && !strchr(" \t\r\n", *ptr)) ptr++;
			size_t len = ptr - start;
			char* token = malloc(len + 1);
			strncpy_s(token, len + 1, start, len);
			token[len] = '\0';
			tokens[position++] = token;
		}

		if (position >= bufsize) {
			bufsize *= 2;
			char** new_tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!new_tokens) {
				free(tokens);
				fprintf(stderr, "Reallocation error\n");
				exit(EXIT_FAILURE);
			}
			tokens = new_tokens;
		}
	}
	tokens[position] = NULL;
	return tokens;
}
