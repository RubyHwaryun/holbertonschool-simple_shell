#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void print_prompt();


int shell(char **environ) {
    char command[1024];  /* Increase buffer size for longer commands (optional) */
    int status;

    while (1) {
        print_prompt();

        /* Read command from user */
        if (fgets(command, sizeof(command), stdin) == NULL) {
            if (feof(stdin)) {  /* Handle Ctrl+D */
                printf("\n");
                break;
            } else {
                perror("fgets");
                return EXIT_FAILURE;
            }
        }

        /* Remove trailing newline from command */
        command[strcspn(command, "\n")] = '\0';

        /* Check for empty command */
        if (strlen(command) == 0) {
            continue;
        }

        /* Create a child process */
        pid_t child_pid = fork();

        if (child_pid < 0) {
            perror("fork");
            continue;
        } else if (child_pid == 0) {
            /* Child process */
            /* Use execve to execute command with environment */
            execve(command, NULL, environ);
            perror("execve");  /* Print error if execve fails */
            exit(EXIT_FAILURE);
        } else {
            /* Parent process */
            waitpid(child_pid, &status, 0);  /* Wait for child to finish */

            if (!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS) {
                printf("Command failed.\n");
            }
        }
    }

    return EXIT_SUCCESS;
}
