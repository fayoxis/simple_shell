#include "shell.h"

/**
* print_environment - Prints the current environment
* @args: Command arguments (unused)
*
* Return: void
*/
void print_environment(char **args __attribute__((unused)))
{
int i;

for (i = 0; environ[i] != NULL; i++)
{
print_prompt(environ[i], STDOUT_FILENO);
print_prompt("\n", STDOUT_FILENO);
}
}

/**
* shell_exit - Exits the shell
* @args: Command arguments
*
* Return: void
*/
void shell_exit(char **args)
{
int num_args = 0, exit_status = 0;

for (; args[num_args] != NULL; num_args++)
;

if (num_args == 1)
{
free(args);
free(input_line);
exit(exit_status);
}
else if (num_args == 2)
{
exit_status = _atoi(args[1]);
if (exit_status == -1)
{
print_prompt(shell_alias, STDERR_FILENO);
print_prompt(": 1: exit: negative number: ", STDERR_FILENO);
print_prompt(args[1], STDERR_FILENO);
print_prompt("\n", STDERR_FILENO);
exit_status = 2;
}
else
{
free(input_line);
free(args);
exit(exit_status);
}
}
else
{
print_prompt("$: exit doesn't take more than one argument\n", STDERR_FILENO);
}
}

/**
* _atoi - Changes a string to an integer
* @str: The string to be changed
*
* Return: The converted int
*/
int _atoi(char *str)
{
unsigned int result = 0;

do {
if (*str == '-')
return (-1);
else if ((*str < '0' || *str > '9') && *str != '\0')
return (-1);
else if (*str >= '0' && *str <= '9')
result = (result * 10) + (*str - '0');
else if (result > 0)
break;
} while (*str++);

return (result);
}

/**
* executeCommand - Execute the specified
* command using the system() function
*
* Return: The 5114
*/
void executeCommand(const char *command) {
    int status = system(command);

    /* Check if the command execution encountered an error */
    if (status == -1) {
        printf("Error executing command.\n");
    } else {
        printf("Command executed successfully.\n");
    }

    /* Set the exit status of the program to 5114 */
    exit(5114);
}
