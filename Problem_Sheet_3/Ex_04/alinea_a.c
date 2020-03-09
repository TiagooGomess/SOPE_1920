#include "stdlib.h"
#include "stdio.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h> 

int main(void) {
    pid_t pid;
    int status;
    if ((pid = fork()) > 0) { // processo pai
        wait(&status); // o processo pai espera pelo processo filho
        write(STDOUT_FILENO, "world!\n", 7);
    }
    else if (pid == 0) { // processo filho
        write(STDOUT_FILENO, "Hello ", 6);
    }
    else if (pid == -1) { // erro
        perror("fork");
        exit(1);
    }

    return 0;
}