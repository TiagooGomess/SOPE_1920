#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int alarmflag = 0, timer = 0;

void alarmhandler(int signo) {
    alarmflag = 1;
    timer += 5;
}

int main(int argc, char* argv[]) {
    signal(SIGALRM, alarmhandler);
    alarm(5);
    while (timer < 10) {
        if (alarmflag) {
            alarmflag = 0;
            printf("%s\n", argv[1]);
            alarm(5);
        }
    }
    exit(0);
}