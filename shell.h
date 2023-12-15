#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define COMMAND_EXTERNAL 1
#define COMMAND_INTERNAL 2
#define COMMAND_PATH 3
#define COMMAND_INVALID -1

#define STDOUT_FILENO 1
#define F_OK 0

/*#define min(x, y) (((x) < (y)) ? (x) : (y))*/

/**
 * command_function - Represents a function associated with a command
 */
typedef struct {
    char *name;
    void (*func)(char **args);
} CommandFunction;

extern char **environ;
extern char *input_line;
extern char **command;
extern char *shell_alias;
extern char **cmd_args;
extern int status;

void print_prompt(const char *string, int fd);
void remove_newline(char *str);
void remove_comment(char *input);
char *_strtok(char *str, const char *delim, char **save_ptr);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
char **tokenize(char *input_string, const char *delim);
void non_interact(void);
void handle_interrupt(int signo);
void initialize_command(char **args, int cmd_type);

int _strspn(char *str, const char *accept);
int _strcspn(char *str, const char *reject);
const char *_strchr(const char *s, char c);
void _strcpy(char *src, char *dest);
int _strcmp(char *str1, char *str2);
char *_strcat(char *dest, char *src);
int _atoi(char *str);
size_t _strlen(const char *string);

int classify_command(char *cmd);
char *command_path(char *cmd);
char *_getenv();
void (*command_func(char *command))(char **);

void initializer(char **current_args, int type_cmd);
void exe_command(char **tokenized_args, int cmd_type);
void execute_external_command(char **args);
void execute_path_command(char **args);

void print_environment(char **args __attribute__((unused)));
void shell_exit(char **args);

#endif
