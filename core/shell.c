#include "shell.h"

void shell_loop(void)
{
	int status = 1;

	while (status)
	{
		printf("%s", PROMPT);
		char* input = read_input();
		status = execute_command(input);

		free(input);
	}
}

char* read_input(void)
{
	char* input_buffer = malloc(sizeof(char*) * input_buffer_size);

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

	input_buffer[strcmp(input_buffer, "\n")] = 0;
	return input_buffer;

}

int execute_command(char* input)
{
	printf("You entered: %s\n", input);
	return 0;
}