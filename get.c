#include "shell.h"

int count_args(char *input, int size) {
    int count = 0;
    for (int i = 1; i < size; i++) {
        if ((input[i - 1] == ' ' && (input[i] != ' ' && input[i] != '\n')) ||
            (i == 1 && input[i - 1] != ' ')) {
            count++;
        }
    }
    return count;
}

char **get_command(char **input) {
    char **arguments;
    size_t n = 1;
    ssize_t chars_read;
    int arg_count = 0;
    int i, l = 0;

    *input = (char *)malloc(n);
    if (*input == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    chars_read = getline(input, &n, stdin);
    if (chars_read == -1) {
        if (errno != 0) {
            perror("Error reading input");
        }
        free(*input);
        return NULL;
    }

    arg_count = count_args(*input, chars_read);
    if (!arg_count) {
        arguments = (char **)malloc(sizeof(char *));
        if (arguments == NULL) {
            perror("Memory allocation failed");
            free(*input);
            return NULL;
        }
        arguments[0] = strdup(" ");
        if (arguments[0] == NULL) {
            perror("Memory allocation failed");
            free(arguments);
            free(*input);
            return NULL;
        }
        return arguments;
    }

    arguments = (char **)malloc(sizeof(char *) * (arg_count + 1));
    if (arguments == NULL) {
        perror("Memory allocation failed");
        free(*input);
        return NULL;
    }

    for (i = 1; i < chars_read; i++) {
        if ((*input)[i - 1] == ' ' || (*input)[i - 1] == '\t' || (*input)[i - 1] == '\n') {
            (*input)[i - 1] = '\0';
        } else if ((*input)[i - 1] != '\0') {
            arguments[l] = *input + i - 1;
            while ((*input)[i] != ' ' && (*input)[i] != '\t' && (*input)[i] != '\n') {
                i++;
            }
            (*input)[i] = '\0';
            l++;
        }
    }

    arguments[l] = NULL;
    return arguments;
}
