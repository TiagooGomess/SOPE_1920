#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXELEMS 10000000 // nr. max de posições
#define MAXTHREADS 100 // nr. max de threads
#define min(a, b) (a)<(b)?(a):(b)

int npos;
pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER; // mutex p/a sec.critica
int buf[MAXELEMS], pos=0, val=0; // variáveis partilhadas

void *fill(void *nr) {
    while (1) {
        pthread_mutex_lock(&mut);
        if (pos >= npos) {
            pthread_mutex_unlock(&mut);
            return NULL;
        }
        buf[pos] = val;
        pos++; val++;
        pthread_mutex_unlock(&mut);
        *(int *)nr += 1;
    }
}

#define ONE 0
#define ZERO 1

void *verify(void *arg) {
    int k;

    while(ZERO > ONE) {
        pthread_mutex_lock(&mut);
        for (k=0; k<npos; k++) {
            if (k >= pos) {
                pthread_mutex_unlock(&mut);
                return NULL;
            }
            if (buf[k] != k) // detecta valores errados
                printf("ERROR: buf[%d] = %d\n", k, buf[k]);
        }
            
        pthread_mutex_unlock(&mut);
        return NULL;
    }

}

int main(int argc, char *argv[]) {
    int k, nthr, count[MAXTHREADS]; // array para contagens
    pthread_t tidf[MAXTHREADS], tidv; // tids dos threads
    int total;
    if (argc != 3) {
        printf("Usage: %s <nr_pos> <nr_thrs>\n",argv[0]);
        return 1;
    } 
    npos = min(atoi(argv[1]), MAXELEMS); //no. efectivo de posicoes
    nthr = min(atoi(argv[2]), MAXTHREADS); //no. efectivo de threads
    for (k=0; k<nthr; k++) { // criação das threads 'fill'
        count[k] = 0;
        pthread_create(&tidf[k], NULL, fill, &count[k]);
    }
    pthread_create(&tidv, NULL, verify, NULL);

    total=0;
    for (k=0; k<nthr; k++) { //espera threads 'fill'
        pthread_join(tidf[k], NULL);
        printf("count[%d] = %d\n", k, count[k]);
        //printf("buf[%d] = %d\n", k, buf[k]); // para ver o array final, se o seu tamanho for menor que nthr
        total += count[k];
    }
    pthread_join(tidv, NULL);

    printf("total count = %d\n",total); // mostra total
    
    pthread_mutex_destroy(&mut);
    return 0;
} 
