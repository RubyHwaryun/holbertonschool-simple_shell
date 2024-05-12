#include "shell.h"
#include <sys/stat.h> 

extern char **path_var; 

char *find_file(char *command, int *lk)
{
    if (command[0] == '/' || command[0] == '.')
    {
        struct stat st;
        if (!stat(command, &st)) {
            (*lk)++;
            return strdup(command);
        }
        return NULL;
    }

    if (!path_var)
        return NULL;

    char *temp = malloc(MAX_PATH_LENGTH);
    if (temp == NULL)
        return NULL;

    for (int i = 0; path_var[i] != NULL; i++) {
        snprintf(temp, MAX_PATH_LENGTH, "%s/%s", path_var[i], command);
        struct stat st;
        if (!stat(temp, &st)) {
            (*lk)++;
            errno = 0;
            return strdup(temp);
        }
    }
    free(temp);
    return NULL;
}
