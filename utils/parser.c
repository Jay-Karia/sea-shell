#include "shell.h"

char **parse_input(char *input)
{
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    
    if (!tokens)
    {
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    char *ptr = input;
    char *start;
    int in_quotes = 0;

    while (*ptr)
    {
        // Skip whitespace
        while (*ptr && strchr(DELIMITERS, *ptr) && !in_quotes)
            ptr++;
        if (!*ptr)
            break;

        start = ptr;

        // Handle quoted strings
        if (*ptr == '"' || *ptr == '\'')
        {
            char quote = *ptr;
            ptr++;       // Skip opening quote
            start = ptr; // Start after quote

            // Find closing quote
            while (*ptr && *ptr != quote)
                ptr++;
            if (*ptr == quote)
            {
                *ptr = '\0'; // Null terminate
                ptr++;       // Skip closing quote
            }

            tokens[position++] = start;
        }
        else
        {
            // Regular token
            while (*ptr && !strchr(DELIMITERS, *ptr))
                ptr++;
            if (*ptr)
            {
                *ptr = '\0';
                ptr++;
            }
            tokens[position++] = start;
        }

        // Resize if needed
        if (position >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    tokens[position] = NULL;
    return tokens;
}