#include "shell.h"

char **path_var = NULL;

void find_path(char **var, int *i, int *j)
{
    while (var[*i])
    {
        while (var[*i][*j])
        {
            if (var[*i][*j] == '=' && strncmp(var[*i], "PATH=", 5) == 0) 
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
    if (env == NULL)
        return NULL;

    int i = 0, j = 0;
    find_path(env, &i, &j);
    if (i == 0 && j == 0)
    {
        return NULL;
    }
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
    if (path_var == NULL)
        return;

    int i = 0;
    while (path_var[i])
        free(path_var[i++]);
    free(path_var);
}
