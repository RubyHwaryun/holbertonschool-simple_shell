#include "shell.h"

void execute(char **arguments) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
       if (execvp(arguments[0], arguments) < 0) {
            perror(arguments[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        waitpid(pid, &status, 0);
    }
 
    return status;
}
