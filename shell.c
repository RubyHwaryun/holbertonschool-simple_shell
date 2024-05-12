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


int main() {
    while (1) {
        char *input = get_input();
        char **arguments = parse_input(input);
        if (strcmp(arguments[0], "exit") == 0) {
            free(input);
            free(arguments);
            break;
        } else if (strcmp(arguments[0], "env") == 0) {
            print_env();
        } else {
            execute(arguments);
        }
        free(input);
        free(arguments);
    }
    return 0;
}
