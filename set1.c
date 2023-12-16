#include "shell.h"
/**
 * free_s - frees an array of strings
 * @str_arr: array of strings
 */
void free_s(char **str_arr)
{
    if (str_arr == NULL) {
        return;
    }

    while (*str_arr != NULL) {
        free(*str_arr);
        str_arr++;
    }
}


int customGetline(char **ptr, size_t *length) {
    static char buffer[READ_BUF_SIZE];
    static size_t index = 0, bufferLength = 0;
    size_t k;
    ssize_t readResult = 0, seekResult = 0;
    char *p = NULL, *new_p = NULL;
    const char *c; 

    p = *ptr;
    if (p && length)
        seekResult = *length;
    if (index == bufferLength)
        index = bufferLength = 0;

    readResult = read(0, buffer, READ_BUF_SIZE);
    if (readResult == -1 || (readResult == 0 && bufferLength == 0))
        return -1;

    c = strchr(buffer + index, '\n'); // Use strchr instead of _strchr
    k = c ? 1 + (unsigned int)(c - buffer) : bufferLength;
    new_p = realloc(p, seekResult ? seekResult + k : k + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return p ? (free(p), -1) : -1;

    if (seekResult)
        strncat(new_p, buffer + index, k - index);
    else
        strncpy(new_p, buffer + index, k - index + 1);

    seekResult += k - index;
    index = k;
    p = new_p;

    if (length)
        *length = seekResult;
    *ptr = p;
    return seekResult;
}
/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}
