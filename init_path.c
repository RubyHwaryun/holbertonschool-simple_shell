#include "shell.h"

extern char **path_var;

void find_path(char **var, int *i, int *j)
{
    while (var[*i])
    {
        while (var[*i][*j])
        {
            if (var[*i][*j] == '=')
                return;
            (*j)++;
        }
        (*i)++;
        *j = 0;
    }
    *i = 0;
    *j = 0;
}

char **get_path(char **env)
{
    int i = 0, j = 0;
    char **array;

    find_path(env, &i, &j);
    if (i == 0 && j == 0)
    {
        return (NULL);
    }
    char *path = getenv("PATH");
    if (!path)
    {
        return NULL;
    }
    array = _strtok(path, ":");
    if (!array)
    {
        free(array);
        return (NULL);
    }
    return (array);
}

void free_path(void)
{
    int i = 0;

    if (!path_var)
        return;
    while (path_var[i])
        free(path_var[i++]);
    free(path_var);
}
