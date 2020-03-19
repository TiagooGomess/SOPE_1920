#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

int counter = 0;

void sig_usr(int signo) {
    if (signo == SIGUSR1)
        counter++;
    else if (signo == SIGUSR2)
        counter--;
}

int main(void) {
    srand(time(0));
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Error\n");
        exit(1);
    }
    else if (pid == 0) { // filho
        struct sigaction action;
        action.sa_handler = sig_usr;
        sigemptyset(&action.sa_mask);
        action.sa_flags = 0;
        if (sigaction(SIGUSR1,&action,NULL) < 0) {
            fprintf(stderr,"Unable to install SIGUSR1 handler\n");
            exit(2);
        }
        if (sigaction(SIGUSR2,&action,NULL) < 0) {
            fprintf(stderr,"Unable to install SIGUSR2 handler\n");
            exit(3);
        }
        while(1) {
            pause();
            printf("Counter: %d\n", counter);
        }
    }
    else { // pai
        printf("Start looping ...\n");
        for (int i = 0; i < 50; i++) {
            if (rand() % 2 == 0)
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            sleep(1);
        }
        kill(pid, SIGTERM);
    }
    exit(0);
}
