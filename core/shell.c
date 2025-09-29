#include "shell.h"
#include "../lib/linenoise.h"

void shell_loop(void)
{
	int status = 0;

	while (status == 0)
	{
		printf("%s", PROMPT);
		fflush(stdout); // Ensure prompt is displayed

		char* input = NULL;
		size_t len = 0;
		ssize_t read = getline(&input, &len, stdin);
		
		if (read == -1) {
			if (feof(stdin)) {
				printf("\n");
				break; // Exit on EOF (Ctrl+Z on Windows, Ctrl+D on Unix)
			} else {
				perror("getline");
				continue; // Error reading input
			}
		}

		// Remove trailing newline if present
		if (read > 0 && input[read - 1] == '\n') {
			input[read - 1] = '\0';
		}

		// Parse the input
		char** args = parse_input(input);

		status = execute_command(args);

		free(args);
		free(input);
	}
}

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