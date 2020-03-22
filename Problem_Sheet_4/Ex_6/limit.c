#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int delay;

void childhandler(int signo) { /* Executed if child dies before parent */
    int status;
    pid_t pid;
    pid = wait(&status);
    printf("Child %d terminated within %d seconds.\n", pid, delay);
    exit(0);
}

int main(int argc, char *argv[]) {
    pid_t pid;
    signal(SIGCHLD, childhandler);
    pid = fork();
    if (pid == 0) /* child */ 
        execl(argv[2], argv[2], argv[3], NULL);
        
    else { /* parent */ 
        sscanf(argv[1], "%d", &delay); /* read delay from command line */
        sleep(delay);
        printf("Program %s exceeded limit of %d seconds!\n", argv[2], delay);
        kill(pid, SIGKILL);
    }
}