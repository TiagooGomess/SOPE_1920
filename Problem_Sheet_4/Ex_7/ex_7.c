#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int status;
    for (int i = 1; i < argc; i++) {
        pid = fork();
        if (pid == 0) { // child

            execl(argv[i], argv[i], NULL);
            
            fprintf(stderr, "Error\n");
            exit(1);
        }
    }

    while((pid = wait(&status)) != -1 ){
        printf("Child with PID=%d finished with exit code %d\n", pid, WEXITSTATUS(status));
        if (WEXITSTATUS(status) != 0)
            kill(0, SIGKILL); // termina todos os processos em execução que foram lançados pelo programa
    }

    exit(0);
}