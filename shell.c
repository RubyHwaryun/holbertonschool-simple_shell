#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_line(char *line, char ***argv) {
  int num_args = 0;
  char *sep = " ";
  char *token = strtok(line, sep);

  *argv = (char **)malloc(MAX_ARGS * sizeof(char *));
  if (*argv == NULL) {
    perror("malloc");
    exit(1);
  }

  while (token != NULL) {
    (*argv)[num_args++] = strdup(token);
    if ((*argv)[num_args - 1] == NULL) {
      perror("strdup");
      /* Handle the error (e.g., exit or indicate failure) */
      return -1;
    }
    token = strtok(NULL, sep);
  }

  (*argv)[num_args] = NULL;  /* NULL terminate the argument list*/
  return num_args;
}

int execute(char **argv) {
  pid_t pid = fork();
  if (pid == -1) {
    perror("fork");
    return 1;
  } else if (pid == 0) {
    /* Child process */
    if (execve(argv[0], argv, NULL) == -1) {
      perror(argv[0]);
      exit(1);
    }
  } else {
    /* Parent process */
    wait(NULL);
  }

  if (argv[0] == NULL) {  /* Empty command */
    return 1;
  }

  if (strcmp(argv[0], "cd") == 0) {
    if (argv[1] == NULL) {
      chdir(getenv("HOME")) !=0; {
        perror("chdir");
      } /* Change to home directory */
    } else {
      if (chdir(argv[1]) != 0) {
        perror("chdir");
      }
    }
    return 1;
  } else if (strcmp(argv[0], "exit") == 0) {
    exit(0);
  }
  return 1;
}

void print_prompt(void) {
  printf("$ ");
  fflush(stdout);
}

int main(int argc, char *argv[]) {
  size_t line_size = MAX_LINE;
  char *line_buffer = malloc(line_size * sizeof(char));  /* Dynamically allocate memory for line_buffer */
  char **argv_list = NULL;

  if (line_buffer == NULL) {
    perror("malloc");
    return 1;
  }

  if (argc > 1) {  /* Non-interactive mode */
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
      perror("fopen");
      free(line_buffer);  /* Free allocated memory */
      return 1;
    }

    while (getline(&line_buffer, &line_size, fp) != -1) {
      if (line_buffer[strlen(line_buffer) - 1] == '\n') {
        line_buffer[strlen(line_buffer) - 1] = '\0';  /* Remove trailing newline*/
      }
      parse_line(line_buffer, &argv_list);
      execute(argv_list);

      /* Free each argument string after execution */
      int i;
      for (i = 0; argv_list[i] != NULL; i++) {
        free(argv_list[i]);
      }
      free(argv_list);
      argv_list = NULL;  /* Reset for next line */
    }
    fclose(fp);
  } else {
    while (1) {
      print_prompt();
      if (getline(&line_buffer, &line_size, stdin) == -1) {
        break;  /* Exit on EOF */
      }

      if (line_buffer[strlen(line_buffer) - 1] == '\n') {
        line_buffer[strlen(line_buffer) - 1] = '\0';  /* Remove trailing newline*/
      }

      parse_line(line_buffer, &argv_list);
      execute(argv_list);

      /* Free each argument string and argv_list itself after execution */
      int i;
      for (i = 0; argv_list[i] != NULL; i++) {
        free(argv_list[i]);
      }
      free(argv_list);
      argv_list = NULL;  /* Reset for next iteration */
    }
  }

  free(line_buffer);  /* Free dynamically allocated memory for line buffer */
  return 0;
}
