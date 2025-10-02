#ifndef SHELL_BUILTINS_H
#define SHELL_BUILTINS_H

// Builtin function declarations
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);

// Helper functions
int shell_num_builtins();

// External declarations (defined in builtins.c)
extern char *builtin_str[];
extern int (*builtin_func[]) (char **);

#endif