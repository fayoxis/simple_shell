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


void handle_logical_operators(char* commands) {
    char* command = strtok(commands, "&&");
    while (command != NULL) {
        char* or_command = strtok(command, "||");
        bool success = false;
        while (or_command != NULL) {
            if (strcmp(or_command, "&&") != 0 && strcmp(or_command, "||") != 0) {
                char** tokenized_args = tokenize(or_command, " ");
                int cmd_type = classify_command(tokenized_args[0]);
                if (cmd_type != COMMAND_INVALID) {
                    exe_command(tokenized_args, cmd_type);
                    success = true;
                }
                free(tokenized_args);
            }
            or_command = strtok(NULL, "||");
            if (success) {
                break;
            }
        }
        command = strtok(NULL, "&&");
    }
}
