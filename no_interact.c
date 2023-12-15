#include "shell.h"

/**
 * non_interact - handles non-interactive mode
 */
void non_interact(void) {
    char **current_args = NULL;
    int cmd_type = 0;
    size_t buffer_size = 0;
    int exit_status = 0;
    int i;

    if (!isatty(STDIN_FILENO)) {
        while (getline(&input_line, &buffer_size, stdin) != -1) {
            remove_newline(input_line);
            remove_comment(input_line);
            cmd_args = tokenize(input_line, ";");

            for (i = 0; cmd_args[i] != NULL; i++) {
                current_args = tokenize(cmd_args[i], " ");
                if (current_args[0] == NULL) {
                    free(current_args);
                    break;
                }

                cmd_type = classify_command(current_args[0]);
                initialize_command(current_args, cmd_type);
                free(current_args);
            }

            free(cmd_args);
        }

        free(input_line);
        exit(exit_status);
    }
}
