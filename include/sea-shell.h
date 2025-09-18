#ifndef SEA_SHELL_H
#define SEA_SHELL_H

#define PROMPT "~>"
#define HISTORY_LENGTH 1024
#define LINE_BUFFER_SIZE 1024

void shell_loop(void);
char* read_line(void);
char** split_line(char* line);

#endif
