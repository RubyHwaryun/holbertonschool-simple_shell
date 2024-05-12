#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_ARGUMENTS 64

char *get_input() {
    char *input = NULL;
    size_t input_size = 0;
    ssize_t num_chars_read;
    int index = 0;
    char c;

    printf("$ ");

    while ((num_chars_read = read(STDIN_FILENO, &c, 1)) > 0) {
        if (c == '\n') {
            break;
        }
        input = realloc(input, input_size + 1);
        if (input == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        input[index++] = c;
        input_size++;
    }

    if (num_chars_read == -1) {
        perror("Error reading input");
        free(input);
        exit(EXIT_FAILURE);
    }

    if (input_size > 0 && input[input_size - 1] == '\n') {
        input[input_size - 1] = '\0';
    } else {
        input = realloc(input, input_size + 1);
        if (input == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        input[input_size] = '\0';
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
