#include "stdlib.h"
#include "stdio.h"
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t pid;
    pid_t ppid = getppid();
    if ((pid = fork()) == 0) { // processo filho
        while(getppid() == ppid) {
            // o processo filho espera que o processo pai acabe
        }
        write(STDOUT_FILENO, "world!\n", 7);
    }
    else if (pid > 0) { // processo pai
        write(STDOUT_FILENO, "Hello ", 6);
    }
    else if (pid == -1) { // erro
        perror("fork");
        exit(1);
    }

    return 0;
}

/* Neste caso, o processo pai executa sempre primeiro do que o processo filho */