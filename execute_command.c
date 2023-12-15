#include "shell.h"

int status;

/**
 * initializer - intializes execution
 * @current_args: Array representing the current command
 * @type_cmd: Parsed command type
 *
 * Return: void function
 */
void initialize_command(char **current_args, int type_cmd)
{
    pid_t pid;

    if (type_cmd == COMMAND_EXTERNAL || type_cmd == COMMAND_PATH)
    {
        pid = fork();
        if (pid == 0)
            exe_command(current_args, type_cmd);
        else
        {
            waitpid(pid, &status, 0);
            status >>= 8;
        }
    }
    else
        exe_command(current_args, type_cmd);
}

/**
 * exe_command - Executes the specified command based on its type
 * @cmd_args: Array of command arguments
 * @cmd_type: Type of the command (EXTERNAL_COMMAND, INTERNAL_COMMAND, PATH_COMMAND)
 *
 * Return: void function
 */
void exe_command(char **tokenized_args, int cmd_type)
{
    void (*cmd_func)(char **);

    if (cmd_type == COMMAND_EXTERNAL)
    {
        execute_external_command(tokenized_args);
    }
    else if (cmd_type == COMMAND_PATH)
    {
        execute_path_command(tokenized_args);
    }
    else if (cmd_type == COMMAND_INTERNAL)
    {
        cmd_func = command_func(tokenized_args[0]);
        cmd_func(tokenized_args);
    }
    else if (cmd_type == COMMAND_INVALID)
    {
        print_prompt(shell_alias, STDERR_FILENO);
		print_prompt(": 1: ", STDERR_FILENO);
		print_prompt(tokenized_args[0], STDERR_FILENO);
		print_prompt(": No such command\n", STDERR_FILENO);
		status = 127;
    }
}

/**
 * execute_external_command - Executes an external command
 * @args: Array of command arguments
 *
 * Return: void
 */
void execute_external_command(char **args)
{
    if (execve(args[0], args, NULL) == -1)
    {
        perror(_getenv("PWD"));
        exit(2);
    }
}

/**
 * execute_path_command - Executes a command found in the PATH
 * @args: Array of command arguments
 *
 * Return: void
 */
void execute_path_command(char **args)
{
    if (execve(command_path(args[0]), args, NULL) == -1)
    {
        perror(_getenv("PWD"));
        exit(2);
    }
}
