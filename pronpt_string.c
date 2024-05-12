#include "shell.h"

void print_prompt(int status)
{
    if (status)
        printf("#cisfun$ ");
    else
        errno = 0;
}
