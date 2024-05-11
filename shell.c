#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

#define MAX_COMMAND_LENGTH 100

/* Function to display prompt */
void display_prompt() {
    write(STDOUT_FILENO, "$ ", 2); /* Using write instead of printf for prompt */
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;
    int status;
    ssize_t num_read; /* Declaration moved to before any executable statement */

    while (1) {
        /* Display prompt */
        display_prompt();

        /* Read command */
        num_read = read(STDIN_FILENO, command, sizeof(command)); // Declaration moved before the first executable statement
        if (num_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        } else if (num_read == 0) {
            /* Handle EOF */
            write(STDOUT_FILENO, "\nExiting shell...\n", 19); /* Using write instead of printf */
            break;
        }

        /* Null-terminate the command */
        command[num_read - 1] = '\0'; /* Remove newline character */

        /* Fork a child process */
        pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process */
            char *args[] = {command, NULL}; /* Declare arguments array before execve call */
            if (execve(command, args, NULL) == -1) {
                /* Handle command not found */
                char error_msg[100];
                snprintf(error_msg, sizeof(error_msg), "Command not found: %s\n", command);
                write(STDOUT_FILENO, error_msg, strlen(error_msg)); /* Using write instead of printf */
                _exit(EXIT_FAILURE); /* Using _exit instead of exit in child process */
            }
        } else {
            /* Parent process */
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
            if (WIFEXITED(status)) {
                /* Child exited normally */
                if (WEXITSTATUS(status) == EXIT_FAILURE) {
                    char error_msg[100];
                    snprintf(error_msg, sizeof(error_msg), "Command failed: %s\n", command);
                    write(STDERR_FILENO, error_msg, strlen(error_msg)); /* Using write instead of fprintf */
                }
            } else if (WIFSIGNALED(status)) {
                /* Child terminated by signal */
                char error_msg[100];
                snprintf(error_msg, sizeof(error_msg), "Command terminated by signal: %s\n", command);
                write(STDERR_FILENO, error_msg, strlen(error_msg)); /* Using write instead of fprintf */
            }
        }
    }

    return 0;
}
