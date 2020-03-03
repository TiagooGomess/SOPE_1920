#include "stdlib.h"
#include "stdio.h"
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t pid1, pid2;
    if ((pid1 = fork()) > 0) { // processo pai
        write(STDOUT_FILENO, "Hello ", 6);
        if ((pid2 = fork()) == 0) { // filho
            write(STDOUT_FILENO, "friends!\n", 9);
        }
        else if (pid2 > 0) { // pai
            write(STDOUT_FILENO, "my ", 3);
        }
        else if (pid2 == -1) { // erro
            perror("fork");
            exit(1);
        }
    }
    else if (pid1 == -1) { // erro
        perror("fork");
        exit(1);
    }

    return 0;
}
