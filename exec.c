#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int execute_command(char **args) {
    int exec_result = execvp(args[0], args);

    if (exec_result == -1) {
        perror("exec");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS; /* Shouldn't be reached if execvp succeeds */
}
