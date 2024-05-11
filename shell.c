#include "shell.h"

int parse_line(char *line, char **argv) {
  int num_args = 0;
  char *sep = " ";
  char *token = strtok(line, sep);

  while (token != NULL) {
    argv[num_args++] = token;
    token = strtok(NULL, sep);
  }

  argv[num_args] = NULL;  /* NULL terminate the argument list*/
  return num_args;
}

int execute(char **argv) {
  if (argv[0] == NULL) {  /* Empty command */
    return 1;
  }

  if (strcmp(argv[0], "cd") == 0) {
    if (argv[1] == NULL) {
      chdir(getenv("HOME"));  /* Change to home directory */
    } else {
      if (chdir(argv[1]) != 0) {
        perror("hsh");
      }
    }
    return 1;
  } else if (strcmp(argv[0], "exit") == 0) {
    exit(0);
  }

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

  return 1;
}

void print_prompt(void) {
  printf("$ ");
  fflush(stdout);
}

int main(int argc, char *argv[]) {
  char line[MAX_LINE];
  char *argv_list[MAX_ARGS];

  if (argc > 1) {  /* Non-interactive mode */
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
      perror("fopen");
      return 1;
    }

    while (fgets(line, MAX_LINE, fp) != NULL) {
      if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';  /*Remove trailing newline*/
      }
      parse_line(line, argv_list);
      execute(argv_list);
    }

    fclose(fp);
    return 0;
  }

  while (1) {
    print_prompt();
    if (fgets(line, MAX_LINE, stdin) == NULL) {
      break;  /* Exit on EOF */
    }

    if (line[strlen(line) - 1] == '\n') {
      line[strlen(line) - 1] = '\0';  /* Remove trailing newline*/
    }

    parse_line(line, argv_list);
    execute(argv_list);
  }

  return 0;
}
