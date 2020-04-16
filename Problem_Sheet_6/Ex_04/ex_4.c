#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *PrintHello(void *threadnum) {
    sleep(1);
    printf("TID: %lu\tNumber: %d\n", pthread_self(), *(int*)threadnum);
    return threadnum;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s 'number_threads'\n", argv[0]);
        exit(1);
    }

    int num_threads = atoi(argv[1]), t, thrArg[num_threads];
    pthread_t threads[num_threads];
    void * ret;

    for(t=0; t< num_threads; t++) {
        printf("Creating thread %d\n", t);
        thrArg[t] = t;
        pthread_create(&threads[t], NULL, PrintHello, (void *)&thrArg[t]);
    }

    for(t=0; t< num_threads; t++) {
        pthread_join(threads[t], &ret);
        printf("Thread %d finished\n", *(int*)ret);
    }

    pthread_exit(0);
}