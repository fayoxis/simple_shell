#include "shell.h"

/**
 *_strlen - counts length of string
 *@string: string to be counted
 *
 * Return: string length
 */

size_t _strlen(const char *string)
{
size_t len = 0;
if (string != NULL)
{
while (string[len] != '\0')
{
len++;
}
}
return (len);
}

/**
 * handle_interrupt - handles the signal raised by CTRL-C
 * @signum: signal number
 *
 * Return: void
 */
void handle_interrupt(int signum)
{
if (signum == SIGINT)
print_prompt("\n$ ", STDIN_FILENO);
}

/**
 * remove_newline - removes newline characters from a string
 * @str: string to be modified
 */
void remove_newline(char *str)
{
int i = 0;
while (str[i] != '\0')
{
if (str[i] == '\n' || str[i] == '\r')
{
str[i] = '\0';
break;
}
i++;
}
}

/**
 * remove_comment - removes everything after a
 * '#' character, including the '#' character
 * @input: input to be modified
 */
void remove_comment(char *input)
{
int i = 0;
while (input[i] != '\0')
{
if (input[i] == '#')
{
input[i] = '\0';
break;
}
i++;
}
}

/**
 * _strcat - Concatenates two strings
 * @dest: String to be concatenated to
 * @src:  String to concatenate
 *
 * Return: Address of the new string
 */
char *_strcat(char *dest, char *src)
{
char *result = NULL;
int len_dest = _strlen(dest);
int len_src = _strlen(src);
result = malloc(sizeof(*result) * (len_dest + len_src + 1));
_strcpy(dest, result);
_strcpy(src, result + len_dest);
result[len_dest + len_src] = '\0';
return (result);
}
