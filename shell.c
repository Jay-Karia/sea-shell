#include "shell.h"

void shell_loop(void)
{
    char line[1024];
    char **args;
    int status = 0;

    do
    {
        printf("%s", PROMPT);
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break; // Exit on EOF (Ctrl+C or Ctrl+D)
        }

        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        args = parse_input(line);
        if (args[0] != NULL) { // Only execute if there's a command
            status = execute_command(args);
        }

        free(args);
    } while (status == 0);
}
