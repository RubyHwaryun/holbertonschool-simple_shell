#include <stdio.h>
#include <stdlib.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64

char *get_input() {
    char *input = (char *)malloc(MAX_COMMAND_LENGTH * sizeof(char));
    printf("$ ");
    fgets(input, MAX_COMMAND_LENGTH, stdin);
    return input;
}
