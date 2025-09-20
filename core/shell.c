#include "shell.h"

void shell_loop(void)
{
	int status = 0;

	while (status == 0)
	{
		printf("%s", PROMPT);

		char* input = read_input();
		if (input == NULL) {
			printf("\nExiting shell...\n");
			break;
		}

		// Parse the input
		char** args = parse_input(input);

		if (args && args[0]) {
			printf("%s\n", args[0]);
		}

		status = execute_command(args);

		free(args);
		free(input);
	}
}

char* read_input(void)
{
	size_t input_buffer_size = 1024;
	char* input_buffer = malloc(input_buffer_size);

	if (!input_buffer)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	if (!fgets(input_buffer, input_buffer_size, stdin))
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			fprintf(stderr, "Input error\n");
			exit(EXIT_FAILURE);
		}
	}

	// Remove trailing newline character if present
	const size_t len = strlen(input_buffer);
	if (len > 0 && input_buffer[len - 1] == '\n')
	{
		input_buffer[len - 1] = '\0';
	}

	return input_buffer;
}

int execute_command(char** args)
{
	if (args && args[0]) {
		printf("You entered: %s\n", args[0]);
	} else {
		printf("No command entered.\n");
	}
	return 0;
}