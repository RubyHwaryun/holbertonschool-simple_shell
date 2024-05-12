#include "shell.h"

char **_strtok(char *str, char delim)
{
    if (str == NULL)
        return NULL;

    int max_tokens = 10;
    char **array = malloc(sizeof(char *) * max_tokens);
    if (array == NULL)
        return NULL;

    int i = 0;
    char *token = strtok(str, &delim);
    while (token != NULL) {
        array[i++] = strdup(token);
        if (i >= max_tokens) {
            max_tokens *= 2;
            array = realloc(array, sizeof(char *) * max_tokens);
            if (array == NULL)
                return NULL;
        }
        token = strtok(NULL, &delim);
    }
    array[i] = NULL;
    return array;
}
