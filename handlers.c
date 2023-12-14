#include "shell.h"

void tokenize(char *input, char *tokens[]) {
    char *token = strtok(input, " ");
    int i = 0;

    while (token != NULL && i < MAX_TOKENS - 1) {
        tokens[i++] = token;
        token = strtok(NULL, " ");
    }

    tokens[i] = NULL; 
}
