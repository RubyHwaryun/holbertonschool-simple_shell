#include <stdio.h> /* Standard input/output functions */
#include <stdlib.h> /* Standard library functions, including exit */
#include <string.h> /* String manipulation functions */
#include <unistd.h> /* Unix standard function calls, including fork, execve */
#include <sys/wait.h> /* Wait related functions */

#define MAX_LINE 256 /* Maximum length of a command line */

int main() {
  /* Define the prompt string */
  char prompt[] = "#cisfun$ ";
  char line[MAX_LINE];
  int running = 1;

  while (running) {
    /* Print the prompt */
    printf("%s", prompt);

    /* Read user input */
    if (fgets(line, MAX_LINE, stdin) == NULL) {
      /* Handle end of file (Ctrl+D) */
      if (feof(stdin)) {
        printf("\n");
      } else {
        perror("fgets");
      }
      break;
    }

    /* Remove trailing newline */
    line[strcspn(line, "\n")] = '\0';

    if (strcmp(line, "exit") == 0) {
      /* Handle exit command */
      running = 0;
    } else {
      /* Fork a child process */
      pid_t pid = fork();

      if (pid < 0) {
        perror("fork");
        continue;
      } else if (pid == 0) {
        /* Child process */
        /* Replace current process with the desired program */
        if (execve(line, NULL, environ) == -1) {
          printf("./shell: %s: No such file or directory\n", line);
        }
        exit(EXIT_FAILURE);
      } else {
        /* Parent process */
        /* Wait for child process to finish */
        int status;
        wait(&status);
      }
    }
  }

  return 0;
}

