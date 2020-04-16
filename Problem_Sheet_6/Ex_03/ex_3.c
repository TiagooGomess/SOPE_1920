#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

void *PrintHello(void *threadnum) {
    printf("Hello from thread no. %d!\n", *(int *) threadnum);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int t;
    int thrArg[NUM_THREADS]; // alinea_b
    for(t=0; t< NUM_THREADS; t++) {
        printf("Creating thread %d\n", t);
        thrArg[t] = t;
        pthread_create(&threads[t], NULL, PrintHello, (void *)&thrArg[t]);
    }
    pthread_exit(0);
    //exit(0); // se tivermos exit(0) em vez de pthread_exit(0), podem haver threads que ainda não tenham
               // acabado a sua execução quando acabar a função main. Já se usarmos pthread_exit(0), a função
               // main só termina quando todas as threads terminarem.
}