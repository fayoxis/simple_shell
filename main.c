#include "main.h"

void display() {
    printf("$ ");
    fflush(stdout);
}

int main() {
    char *input = NULL;
    size_t input_size = 0;
    char *tokens[MAX_TOKENS];
    pid_t pid;
    int status;

    if (argv == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (1) {
        display();
        if (getline(&input, &input_size, stdin) == -1) {
            printf("\n");
            free(input);
            free(argv); /* Don't forget to free dynamically allocated memory */
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        tokenize(input, tokens);

        /* Fork a child process */
        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process */

            if (execve(tokens[0], tokens, NULL) == -1) {
                perror("./shell");
                exit(EXIT_FAILURE);
            }
        } else {
            /* Parent process */
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                printf("Command not found: %s\n", input);
            }
        }
    }

    free(input);
    free(argv);

    return 0;
}
