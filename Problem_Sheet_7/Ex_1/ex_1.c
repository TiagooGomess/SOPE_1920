/*
a)
Pretende-se um programa multithreaded que preencha um array comum com o máximo
de 10000000 de entradas em que cada entrada deve ser preenchida com um valor igual
ao seu índice. Devem ser criados vários threads concorrentes para executar esse
preenchimento. Após o preenchimento, um último thread deverá verificar a correcção
desse preenchimento. O número efectivo de posições do array a preencher e o número
efectivo de threads devem ser passados como parâmetros ao programa.
Segue-se uma solução utilizando as funções fill() e verify() para os threads de
preenchimento e verificação. Além disso toma-se nota do número de posições
preenchidas por cada thread fill() (no array count). Os threads partilham globalmente
o array a preencher (buf), a posição actual, e o valor de preenchimento actual (que
por acaso é igual ao índice actual).

b)
Quando eliminamos as chamadas a pthread_mutex_lock() e pthread_mutex_unlock() na função
fill(), a função verify emite erros, já que as threads passam a não estar sincronizadas,
podendo alterar variáveis globais ao mesmo tempo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXELEMS 10000000 // nr. max de posicoes
#define MAXTHREADS 100 // nr. max de threads
#define min(a, b) (a)<(b)?(a):(b)

int npos;
pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER; // mutex p/a sec.critica
int buf[MAXELEMS], pos=0, val=0; // variaveis partilhadas

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

void *verify(void *arg) {
    int k;
    for (k=0; k<npos; k++)
    if (buf[k] != k) // detecta valores errados
        printf("ERROR: buf[%d] = %d\n", k, buf[k]);
    return NULL;
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
    for (k=0; k<nthr; k++) { // criacao das threads 'fill'
        count[k] = 0;
        pthread_create(&tidf[k], NULL, fill, &count[k]);
    }
    total=0;
    for (k=0; k<nthr; k++) { //espera threads 'fill'
        pthread_join(tidf[k], NULL);
        printf("count[%d] = %d\n", k, count[k]);
        //printf("buf[%d] = %d\n", k, buf[k]); // para ver o array final, se o seu tamanho for menor que nthr
        total += count[k];
    }
    printf("total count = %d\n",total); // mostra total
    pthread_create(&tidv, NULL, verify, NULL);
    pthread_join(tidv, NULL); // espera thread 'verify'
    return 0;
} 
