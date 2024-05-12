#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_PATH_LENGTH 1024
#define MAX_ENV_VARIABLES 256
#define MAX_ENV_LENGTH 1024
#define MAX_TOKEN_LENGTH 64

extern char **environ;

char *get_input();
char **parse_input(char *input);
void execute(char **arguments);
void print_env();

#endif
