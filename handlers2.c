#include "shell.h"

/**
 * _strspn -length of a prefix substring
 * @str: string to be searched
 * @accept: string containing characters to match
 * Return: no of bytes in the initial
 * segment of `str` which are part of `accept`
 */
int _strspn(char *str, const char *accept) {
int i = 0;
int match = 0;
while (str[i] != '\0') {
if (_strchr(accept, str[i]) == NULL)
break;
match++;
i++;
}
return (match);
}

/**
 * _strcspn - computes segment of `str`
 * which consists of characters not in `reject`
 * @str: string to be searched
 * @reject: string containing characters to reject
 *
 * Return: index at which a char in `str` exists in `reject`
 */
int _strcspn(char *str, const char *reject)
{
int len = 0, i;
for (i = 0; str[i] != '\0'; i++)
{
if (_strchr(reject, str[i]) != NULL)
break;
len++;
}
return (len);
}

/**
 * _strchr - locates a char in a string
 * @s: string to be searched
 * @c: char to be checked
 *
 * Return: pointer to the first occurrence of `c` in `s`
 */
const char *_strchr(const char *s, char c)
{
int i = 0;
for (; s[i] != c && s[i] != '\0'; i++)
;
if (s[i] == c)
return ((s + i));
else
return (NULL);
}


/**
 * _strcpy - Copies a string to another buffer
 * @src: Source to copy from
 * @dest: Destination to copy to
 *
 * Return: void
 */
void _strcpy(char *src, char *dest)
{
int i = 0;
for (; src[i] != '\0'; i++)
dest[i] = src[i];
dest[i] = '\0';
}

/**
 * _strcmp - Compare two strings
 * @str1: First string to be compared
 * @str2: Second string to be compared
 *
 * Return: Difference of the two strings
 */
int _strcmp(char *str1, char *str2)
{
int i = 0;
while (str1[i] != '\0')
{
if (str1[i] != str2[i])
break;
i++;
}
return ((str1[i] - str2[i]));
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
