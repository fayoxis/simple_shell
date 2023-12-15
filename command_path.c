#include "shell.h"

/**
* classify_command - Classifies the type of the command
* @cmd: The command to be analyzed
*
* Return: An integer constant representing the type of the command:
*         - COMMAND_EXTERNAL (1) for commands like /bin/ls
*         - COMMAND_INTERNAL (2) for commands like exit, env
*         - COMMAND_PATH (3) for commands found in the PATH like ls
*         - COMMAND_INVALID (-1) for invalid commands
*/

int classify_command(char *cmd)
{
int i;
char *internal_commands[] = {"env", "exit", NULL};
char *path = NULL;

for (i = 0; cmd[i] != '\0'; i++)
{
if (cmd[i] == '/')
return (COMMAND_EXTERNAL);
}

for (i = 0; internal_commands[i] != NULL; i++)
{
if (_strcmp(cmd, internal_commands[i]) == 0)
return (COMMAND_INTERNAL);
}

/* Placeholder for check_path function, replace with actual implementation */
path = command_path(cmd);
if (path != NULL)
{
free(path);
return (COMMAND_PATH);
}

return (COMMAND_INVALID);
}


/**
* command_path - Finds the full path of a command in the PATH environment
* @cmd: The command to be located
*
* Return: The full path where the command is found, or NULL if not found
*/
char *command_path(char *cmd)
{
char **path_dirs = NULL;
char *temp, *temp_concat, *path_copy;
char *path_env = _getenv("PATH");
int i;

if (path_env == NULL || _strlen(path_env) == 0)
return (NULL);

path_copy = malloc(strlen(path_env) + 1);
_strcpy(path_env, path_copy);

path_dirs = tokenize(path_copy, ":");
for (i = 0; path_dirs[i] != NULL; i++)
{
temp_concat = _strcat(path_dirs[i], "/");
temp = _strcat(temp_concat, cmd);
if (access(temp, F_OK) == 0)
{
free(temp_concat);
free(path_dirs);
free(path_copy);
return (temp);
}
free(temp);
free(temp_concat);
}

free(path_copy);
free(path_dirs);
return (NULL);
}

/**
* _getenv - gets the value of an environment variable
* @var_name: name of the environment variable
*
* Return: the value of the variable as a string
*/
char *_getenv(char *var_name)
{
char **env_var;
char *pair_pointer;
char *name_dupli;

for (env_var = environ; *env_var != NULL; env_var++)
{
for (pair_pointer = *env_var, name_dupli = var_name;
*pair_pointer == *name_dupli; pair_pointer++, name_dupli++)
{
if (*pair_pointer == '=')
break;
}
if ((*pair_pointer == '=') && (*name_dupli == '\0'))
return (pair_pointer + 1);
}

return (NULL);
}

/**
* command_func - Retrieves a function based on the command given and a mapping
* @command: String to check against the mapping
*
* Return: Pointer to the proper function, or NULL on fail
*/
void (*command_func(char *command))(char **)
{
int i;
CommandFunction command_mapping[] = {
{"env", print_environment},
{"exit", shell_exit}
};

for (i = 0; i < (int)(sizeof(command_mapping)
/ sizeof(command_mapping[0])); i++)
{
if (_strcmp(command, command_mapping[i].name) == 0)
return (command_mapping[i].func);
}

return (NULL);
}


