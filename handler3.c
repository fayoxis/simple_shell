#include "shell.h" 

int last_exit_code = 0;

char* replace_vars(char* command) {
    char* replaced_command = malloc(strlen(command) + 1);
    char* token;
    char* rest = command;
    char buffer[10];

    while ((token = strtok_r(rest, " ", &rest))) {
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
    char** tokenized_args = tokenize_arguments(or_command);
    int cmd_type = determine_command_type(tokenized_args);
    while (command != NULL) {
        char* or_command = strtok(command, "||");
        bool success = false;
        while (or_command != NULL) {
            
            exe_command(tokenized_args, cmd_type);

            success = true;
            break;
        }
        if (!success) {
            break;
        }
        command = strtok(NULL, "&&");
    }
}


