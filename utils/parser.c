#include <stdio.h>
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

	char* token = strtok_s(input, " \t\r\n", &input);
    while (token != NULL) {
        tokens[position++] = token;

        if (position >= bufsize) {
            bufsize *= 2;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Reallocation error\n");
                exit(EXIT_FAILURE);
            }
        }

		token = strtok_s(NULL, " \t\r\n", &input);
    }
    tokens[position] = NULL;
    return tokens;
}
