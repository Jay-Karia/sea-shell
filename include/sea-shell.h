#ifndef SEA_SHELL_H
#define SEA_SHELL_H

#define PROMPT "~>"
#define HISTORY_LENGTH 1024
#define LINE_BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

void shell_loop(void);
char* read_line(void);
char** tokenize(char* line);
int sea_shell_launch(char** args);
int execute(char** args);

#endif
