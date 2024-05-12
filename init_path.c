#include "shell.h"

char **_strtok(char *str, char delim);

char **path_var = NULL;

void find_path(char **var, int *i, int *j)
{
    while (var[*i])
    {
        while (var[*i][*j])
        {
            if (var[*i][*j] == '=' && strcmp(var[*i], "PATH=") == 0) 
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

    if (env == NULL)
        return NULL;

    find_path(env, &i, &j);

    if (i == 0 && j == 0)
        return NULL;

    j += 5; 
    path_var = _strtok(env[i] + j, ':');

    if (!path_var)
    {
        free(path_var);
        return NULL;
    }

    return path_var;
}

void free_path(void)
{
    int i = 0; 

    if (path_var == NULL)
        return;

    while (path_var[i])
        free(path_var[i++]);

    free(path_var);
}
