#include "shell.h"


/**
 * _strtok - tokenizes a string
 * @str: string to be tokenized
 * @delim: delimiter to be used to tokenize the string
 * @save_ptr: pointer to be used to keep track of the next token
 *
 * Return: The next available token
 */
char *_strtok(char *str, const char *delim, char **save_ptr) {
    char *token_start;
    char *token_end;

    if (str == NULL)
        str = *save_ptr;

    token_start = str + _strspn(str, delim);

    if (*token_start == '\0') {
        *save_ptr = token_start;
        return (NULL);
    }

    token_end = token_start + _strcspn(token_start, delim);

    if (*token_end == '\0') {
        *save_ptr = token_end;
        return token_start;
    }

    *token_end = '\0';
    *save_ptr = token_end + 1;

    return token_start;
}

/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to the memory previously allocated with a call to malloc
 * @old_size: size of ptr
 * @new_size: size of the new memory to be allocated
 *
 * Return: pointer to the address of the new memory block
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size) {
    void *new_block;
    size_t i;

    if (ptr == NULL) {
        new_block = malloc(new_size);
        return new_block;
    } else if (new_size == old_size) {
        return ptr;
    } else if (new_size == 0 && ptr != NULL) {
        free(ptr);
        return NULL;
    } else {
        new_block = malloc(new_size);
        if (new_block != NULL) {
            for (i = 0; i < old_size && i < new_size; i++) {
                *((char *)new_block + i) = *((char *)ptr + i);
            }
            free(ptr);
            return new_block;
        } else {
            return NULL;
        }
    }
}



/**
 * tokenize - tokenizes input and stores it into an array
 * @input_string: input to be parsed
 * @delim: delimiter to be used, needs to be one character string
 *
 * Return: array of tokens
 */

char **tokenize(char *input_string, const char *delim) {
    int num_tokens = 0;
    char **tokens = NULL;
    char *token;
    static char *save_ptr;  

    token = _strtok(input_string, delim, &save_ptr);

    while (token != NULL) {
        tokens = _realloc(tokens, sizeof(*tokens) * num_tokens, sizeof(*tokens) * (num_tokens + 1));
        tokens[num_tokens] = token;
        token = _strtok(NULL, delim, &save_ptr);  
        num_tokens++;
    }

    tokens = _realloc(tokens, sizeof(*tokens) * num_tokens, sizeof(*tokens) * (num_tokens + 1));
    tokens[num_tokens] = NULL;

    return tokens;
}
