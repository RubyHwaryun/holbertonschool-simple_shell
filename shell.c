#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

#define MAX_ARGUMENTS 64

char *get_input() {
    ssize_t num_chars_read;
    char *input = NULL;
    size_t input_size = 0;

    printf("$ ");
    num_chars_read = getline(&input, &input_size, stdin);

    if (num_chars_read == -1) {
        if (feof(stdin)) {
            fprintf(stderr, "Error: End of file reached\n");
        } else if (ferror(stdin)) {
            perror("Error reading input");
        }
        free(input);
        exit(EXIT_FAILURE);
    }
    if (input[num_chars_read - 1] == '\n') {
        input[num_chars_read - 1] = '\0';
    }
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
