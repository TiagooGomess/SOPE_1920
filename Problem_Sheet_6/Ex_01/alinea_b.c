#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define STDERR 2
#define NUMITER 10000

void * thrfunc(void * arg) {
    int i, value = *(int *) arg;
    char argString[2];
    fprintf(stderr, "Starting thread %d\n", value);
    sprintf(argString, "%d", value);
    for (i = 1; i <= NUMITER; i++)
        write(STDERR,argString,1);
    return NULL;
}

int main() {
    pthread_t ta, tb;
    int arg1 = 1, arg2 = 2;
    pthread_create(&ta, NULL, thrfunc, &arg1);
    pthread_create(&tb, NULL, thrfunc, &arg2);
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    return 0;
}