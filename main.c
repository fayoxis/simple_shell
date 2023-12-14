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
  char *argv[];
  int status;

    while (1) {
        display();
        if (getline(&input, &input_size, stdin) == -1) {
            printf("\n");
            free(input);
            break;
        }

        
        input[strcspn(input, "\n")] = '\0';

        /* Fork a child process*/
        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            
            argv[] = { input, NULL };

           
            if (execve(input, argv, NULL) == -1) {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        } else {
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

    return 0;
}
