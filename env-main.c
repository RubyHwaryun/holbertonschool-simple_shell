#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

extern char **environ;  /* Declare external variable for environment */

int main(int argc, char *argv[]) {
    int shell_status = shell(environ);  /* Pass environment to shell */
    return shell_status;
}
