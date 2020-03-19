#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int counter = 0;

void sig_usr(int signo) {
    if (signo == SIGUSR1) 
        counter++;
    else if (signo == SIGUSR2) 
        counter--;
}

int main(void) {
    struct sigaction action;
    action.sa_handler = sig_usr;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGUSR1,&action,NULL) < 0) {
        fprintf(stderr,"Unable to install SIGUSR1 handler\n");
        exit(1);
    }
    if (sigaction(SIGUSR2,&action,NULL) < 0) {
        fprintf(stderr,"Unable to install SIGUSR2 handler\n");
        exit(2);
    }
    while(1) {
        sleep(1);
        printf("Counter: %d\n", counter);
    }
        
    exit(0);
}
