#include "shell.h"

int execute_command(char **args)
{
    if (args[0] == NULL)
    {
        return 1;
    }

    for (int i = 0; i < shell_num_builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }

    return launch_shell(args);
}