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
int num_args = 0, shell_value.exit_status = 0;

for (; args[num_args] != NULL; num_args++)
;

if (num_args == 1)
{
free(args);
free(shell_value.input_line);
exit(shell_value.exit_status);
}
else if (num_args == 2)
{
shell_value.exit_status = _atoi(args[1]);
if (shell_value.exit_status == -1)
{
print_prompt(shell_value.shell_alias, STDERR_FILENO);
print_prompt(": 1: exit: negative number: ", STDERR_FILENO);
print_prompt(args[1], STDERR_FILENO);
print_prompt("\n", STDERR_FILENO);
shell_value.exit_status = 2;
}
else
{
free(shell_value.input_line);
free(args);
exit(shell_value.exit_status);
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
