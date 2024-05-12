#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 2048
#define MAX_ARGS 64

int parse_line(char *line, char ***argv);
int execute(char **argv);
void print_prompt(void);

#endif
