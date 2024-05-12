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

char **parse_input(char *input) {
    char **arguments = (char **)malloc(MAX_ARGUMENTS * sizeof(char *));
    char *argument = strtok(input, " \n");
    int i = 0;
    while (argument != NULL) {
        arguments[i++] = argument;
        argument = strtok(NULL, " \n");
    }
    arguments[i] = NULL;
    return arguments;
}

