#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo) {
    printf("In SIGINT handler ...\n");
}

int main(void) {
    int time = 30;
    struct sigaction action;
    action.sa_handler = sigint_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT,&action,NULL);
    while(time > 0) {
        printf("Sleeping for %d seconds ...\n", time);
        time = sleep(time);
    }
    printf("Waking up ...\n");
    exit(0);
} 