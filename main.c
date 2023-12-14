#include "shell.h"

#define MAX_SIZE 1024

void display() {
    printf("$ ");
    fflush(stdout);
}

int main() {
    char *input = NULL;
    size_t input_size = 0;
    pid_t pid;
    char **argv = malloc(MAX_SIZE * sizeof(char *));
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

        /* Fork a child process */
        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process */

            /* Assign values to argv */
            argv[0] = input;
            argv[1] = NULL;

            if (execve(input, argv, NULL) == -1) {
                perror("shell");
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
