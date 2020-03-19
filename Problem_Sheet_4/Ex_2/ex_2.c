#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void sigint_handler(int signo) {
    printf("Entering SIGINT handler ...\n");
    sleep(10);
    printf("Exiting SIGINT handler ...\n");
}

void sigterm_handler(int signo) {
    printf("Entering SIGTERM handler ...\n");
    printf("Exiting SIGTERM handler ...\n");
}

int main(void) {
    struct sigaction action1, action2;
    action1.sa_handler = sigint_handler;
    action2.sa_handler = sigterm_handler;
    sigemptyset(&action1.sa_mask);
    sigemptyset(&action2.sa_mask);
    action1.sa_flags = 0;
    action2.sa_flags = 0;
    if (sigaction(SIGINT,&action1,NULL) < 0) {
        fprintf(stderr,"Unable to install SIGINT handler\n");
        exit(1);
    }
    if (sigaction(SIGTERM,&action2,NULL) < 0) {
        fprintf(stderr, "Unable to install SIGTERN handler\n");
        exit(2);
    }
    printf("Try me with CTRL-C ...\n");
    while(1)
        pause();
    exit(0);
}

/*
a)
Quando teclamos Ctrl+C, o sinal SIGINT é processado de maneira a esperar 10 segundos. Durante esses 10 segundos,
nada é processado. Como temos um ciclo infinito no programa, por muitas vezes que teclemos Ctrl+C, o programa
nunca termina, pelo que temos que recorrer ao comando kill <pid> para o terminar.

b)
Quando enviamos o comando kill (sinal SIGTERM) ao processo, este termina.

c)
a)
Quando teclamos Ctrl+C, o sinal SIGINT é processado de maneira a esperar 10 segundos. Durante esses 10 segundos,
quando enviamos o comando kill (signal SIGTERM) ao processo, o handler desse sinal é executado. Para terminar este
programa, é preciso enviar o comando kill -kill <pid>.
*/