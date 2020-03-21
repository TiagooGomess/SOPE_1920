#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int status;
pid_t pid;

void sigchld_handler(int signo) {
    pid = wait(&status);
    if (pid != -1)
        printf("PARENT: child with PID=%d terminated with exit code %d\n",pid,WEXITSTATUS(status));
}

int main(void) {
    int i, n;

    struct sigaction action;
    action.sa_handler = sigchld_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGCHLD,&action,NULL);

    for (i=1; i<=10; i++) {
        pid=fork();
        if (pid == 0) {
            printf("CHILD no. %d (PID=%d) working ... \n",i,getpid());
            sleep(15); // child working ...
            printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());
            exit(0);
        }
    }

    printf("PARENT: working hard ...\n");
    n=20;
    while((n=sleep(n))!=0);
    printf("PARENT: end of task\n");
    

    exit(0);
}
