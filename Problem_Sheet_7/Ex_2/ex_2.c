#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define STDERR 2

int N = 50000;
pthread_mutex_t mut;

void * thrfunc(void * arg) {
    
    int value = *(int *) arg;
    char argString[2];
    int* result = malloc(sizeof(int));
    *result = 0;
    fprintf(stderr, "Starting thread %d\n", value);
    sprintf(argString, "%d", value);
    
    while (N > 1) {
        pthread_mutex_lock(&mut);
        write(STDERR,argString,1);
        N--;
        (*result)++;
        pthread_mutex_unlock(&mut);
    }
    
    return result;
}

int main() {
    pthread_t ta, tb;
    int arg1 = 1, arg2 = 2;
    void *ret1, *ret2;

    if (pthread_mutex_init(&mut, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 

    pthread_create(&ta, NULL, thrfunc, &arg1);
    pthread_create(&tb, NULL, thrfunc, &arg2);
    pthread_join(ta, &ret1);
    pthread_join(tb, &ret2);

    printf("\n\nA thread A escreveu %d caracteres\n", *(int*) ret1);
    printf("A thread B escreveu %d caracteres\n", *(int*) ret2);
    printf("\nO número de caracteres escritos é %d\n", *(int*) ret1 + *(int*) ret2);

    pthread_mutex_destroy(&mut);
    return 0;
}
