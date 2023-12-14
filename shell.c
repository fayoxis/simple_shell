#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_SIZE 1024
#define MAX_TOKENS 64

/**
 * Function to get an array of directories from the PATH environment variable.
 * Returns an array of directory strings.
 */
char **get_path_directories() {
    char *path = getenv("PATH");
    int num_directories;

    if (path == NULL) {
        fprintf(stderr, "PATH environment variable not found.\n");
        exit(EXIT_FAILURE);
    }

    /* Count the number of directories in PATH*/
    num_directories = 1;
    for (char *c = path; *c != '\0'; ++c) {
        if (*c == ':') {
            num_directories++;
        }
    }

    /* Allocate memory for the array of directory strings*/
    char **directories = malloc(num_directories * sizeof(char *));
    if (directories == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    /* Tokenize the PATH variable and populate the array*/
    int index = 0;
    char *token = strtok(path, ":");
    while (token != NULL) {
        directories[index++] = token;
        token = strtok(NULL, ":");
    }
    directories[index] = NULL;

    return directories;
}

/**
 * Displays the shell prompt.
 */
void display() {
    printf("$ ");
    fflush(stdout);
}

/**
 * Tokenizes the input string into an array of tokens.
 */
void tokenize(char *input, char *tokens[]) {
    char *token = strtok(input, " ");
    int i = 0;

    while (token != NULL && i < MAX_TOKENS - 1) {
        tokens[i++] = token;
        token = strtok(NULL, " ");
    }

    tokens[i] = NULL; 
}

int main() {
    char *input = NULL;
    size_t input_size = 0;
    char *tokens[MAX_TOKENS];
    pid_t pid;
    int status;

    /* Get the array of directories from PATH*/
    char **path_directories = get_path_directories();

    
    printf("Directories in PATH:\n");
    for (int i = 0; path_directories[i] != NULL; ++i) {
        printf("%s\n", path_directories[i]);
    }

    while (1) {
        display();
        if (getline(&input, &input_size, stdin) == -1) {
            printf("\n");
            free(input);
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        /* Tokenize the input*/
        tokenize(input, tokens);

        
        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process*/

            /* Search for the command in PATH*/
            for (int i = 0; path_directories[i] != NULL; ++i) {
                char *command_path = malloc(strlen(path_directories[i]) + strlen(tokens[0]) + 2);
                if (command_path == NULL) {
                    perror("malloc");
                    exit(EXIT_FAILURE);
                }

                sprintf(command_path, "%s/%s", path_directories[i], tokens[0]);

                /* Execute the command using execve*/
                if (execve(command_path, tokens, NULL) == -1) {
                    /* Continue searching in the next directory if execve fails*/
                    free(command_path);
                    continue;
                } else {
                    /* execve succeeded, so this block won't be executed*/
                    free(command_path);
                    exit(EXIT_SUCCESS);
                }
            }

            
            fprintf(stderr, "Command not found: %s\n", tokens[0]);
            exit(EXIT_FAILURE);
        } else {
            /* Parent process*/
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                printf("Command not found: %s\n", input);
            }
        }
    }

    /* Free allocated memory*/
    free(input);
    for (int i = 0; path_directories[i] != NULL; ++i) {
        free(path_directories[i]);
    }
    free(path_directories);

    return 0;
}
