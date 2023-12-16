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


char* getline() {
    static char buffer[BUFFER_SIZE];
    static int buffer_index = 0;
    static int buffer_size = 0;

    char* line = NULL;
    int line_size = 0;
    char current_char;

    while (1) {
    
        if (buffer_index >= buffer_size) {
            buffer_size = read(buffer, sizeof(char), BUFFER_SIZE, stdin);
            buffer_index = 0;

            if (buffer_size == 0)
                break;
        }

        current_char = buffer[buffer_index++];

        if (current_char == '\n')
            break;

        line = _realloc(line, (line_size + 1) * sizeof(char));
        line[line_size++] = current_char;
    }
    line = _realloc(line, (line_size + 1) * sizeof(char));
    line[line_size] = '\0';

    return line;
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
