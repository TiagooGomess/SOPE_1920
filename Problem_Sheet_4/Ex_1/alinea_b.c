#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo) {
    printf("In SIGINT handler ...\n");
}

int main(void) {
    int time = 30;
    if (signal(SIGINT,sigint_handler) < 0) {
        fprintf(stderr,"Unable to install SIGINT handler\n");
        exit(1);
    }
    while (time > 0) {
        printf("Sleeping for %d seconds ...\n", time);
        time = sleep(time);
    }
    printf("Waking up ...\n");
    exit(0);
}