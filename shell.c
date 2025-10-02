#include "shell.h"
#include <windows.h>
#include <process.h>

char current_dir[MAX_PATH];

void shell_loop(void)
{
    char line[1024];
    char **args;
    int status = 0;

    GetCurrentDirectory(MAX_PATH, current_dir);

    do
    {
        printf("%s%s", current_dir, PROMPT);
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            printf("\n");
            break; // Exit on EOF (Ctrl+C or Ctrl+D)
        }

        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        args = parse_input(line);
        if (args[0] != NULL)
        { // Only execute if there's a command
            status = execute_command(args);
        }

        free(args);
    } while (status == 0);
}

int launch_shell(char **args)
{
    // Windows implementation using CreateProcess
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char cmdline[1024] = "";

    // Build command line from args
    for (int i = 0; args[i] != NULL; i++)
    {
        if (i > 0)
            strcat(cmdline, " ");
        strcat(cmdline, args[i]);
    }

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Start the child process
    if (!CreateProcess(NULL,
                       cmdline,
                       NULL,
                       NULL,
                       FALSE,
                       0,
                       NULL,
                       NULL,
                       &si,
                       &pi))
    {
        printf("Unknown command: %s\n", args[0]);
    }

    // Wait until child process exits
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}