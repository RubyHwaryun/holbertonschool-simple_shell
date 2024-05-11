#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#define MAX_COMMAND_LENGTH 100

void display_prompt() {
    printf("$ ");
    fflush(stdout);
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        /* Display prompt */
        display_prompt();

        /* Read command */
        if (fgets(command, sizeof(command), stdin) == NULL) {
            /* Handle EOF */
            if (feof(stdin)) {
                printf("\nExiting shell...\n");
                break;
            } else if (ferror(stdin)) {
                perror("fgets");
                exit(EXIT_FAILURE);
            }
        }

        /* Remove newline character */
        command[strcspn(command, "\n")] = 0;

        /* Fork a child process */
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process */
            if (execlp(command, command, NULL) == -1) {
                /* Handle command not found */
                printf("Command not found: %s\n", command);
                exit(EXIT_FAILURE);
            }
        } else {
            /* Parent process */
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
            if (WIFEXITED(status)) {
                /* Child exited normally */
                if (WEXITSTATUS(status) == EXIT_FAILURE) {
                    fprintf(stderr, "Command failed: %s\n", command);
                }
            } else if (WIFSIGNALED(status)) {
                /* Child terminated by signal */
                fprintf(stderr, "Command terminated by signal: %s\n", command);
            }
        }
    }

    return 0;
}
