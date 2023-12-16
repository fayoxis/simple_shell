#include "shell.h" 

int last_exit_code = 0;

char* replace_vars(char* command) {
    char* replaced_command = malloc(strlen(command) + 1);
    char* token;
    char* rest = command;
    char buffer[10];

    while ((token = _strtok(rest, " ", &rest))) {
        if (strcmp(token, "$?") == 0) {
            sprintf(buffer, "%d", last_exit_code);
            strcat(replaced_command, buffer);
        } else if (strcmp(token, "$$") == 0) {
            sprintf(buffer, "%d", getpid());
            strcat(replaced_command, buffer);
        } else {
            strcat(replaced_command, token);
        }

        strcat(replaced_command, " ");
    }

    replaced_command[strlen(replaced_command) - 1] = '\0';
    return replaced_command;
}


void process_logical_operators(char **commands, int num_commands) {
    int i = 0;
    while (i < num_commands) {
        if (i + 1 < num_commands) {
            if (strcmp(commands[i+1], "&&") == 0) {
                if (exe_command(commands[i])) {
                    i += 2;
                    continue;
                }
            } else if (strcmp(commands[i+1], "||") == 0) {
                if (!exe_command(commands[i])) {
                    i += 2;
                    continue;
                }
            }
        }
        char *tokenized_args[64];
        char *token;
        int j = 0;
        token = _strtok(commands[i], " ");
        while (token != NULL) {
            tokenized_args[j++] = token;
            token = _strtok(NULL, " ");
        }
        tokenized_args[j] = NULL;
        exe_command(tokenized_args, COMMAND_EXTERNAL);
        i++;
    }
}

