#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 4

typedef struct {
    int num1, num2;
} Nums;

void *printTID(void *threadnum) {
    sleep(1);
    printf("TID: %lu\tNumber: %d\n", pthread_self(), *(int*)threadnum);
    return threadnum;
}

void *addiction(void *arg) {
    Nums numbers = *(Nums *) arg;
    printf("%d + %d = %d\n", numbers.num1, numbers.num2, numbers.num1 + numbers.num2);
    return NULL;
}

void *subtraction(void *arg) {
    Nums numbers = *(Nums *) arg;
    printf("%d - %d = %d\n", numbers.num1, numbers.num2, numbers.num1 - numbers.num2);
    return NULL;
}

void *multiplication(void *arg) {
    Nums numbers = *(Nums *) arg;
    printf("%d * %d = %d\n", numbers.num1, numbers.num2, numbers.num1 * numbers.num2);
    return NULL;
}

void *division(void *arg) {
    Nums numbers = *(Nums *) arg;
    if (numbers.num2 != 0)
        printf("%d / %d = %f\n", numbers.num1, numbers.num2, (double) numbers.num1 / numbers.num2);
    else
        fprintf(stderr, "Division by 0\n");
    return NULL;
}



int main(void) {
    int t, num1, num2;
    pthread_t threads[NUM_THREADS];
    //void * ret;
    Nums numbers[NUM_THREADS];

    printf("\nPrimeiro número: ");
    scanf("%d", &num1);
    printf("Segundo número: ");
    scanf("%d", &num2);
    printf("\n------------------------\n\n");
    
    for(t=0; t< NUM_THREADS; t++) {
        numbers[t].num1 = num1;
        numbers[t].num2 = num2;
        switch (t) {
        case 0:
            pthread_create(&threads[t], NULL, addiction, (void *)&numbers[t]);
            break;
        case 1:
            pthread_create(&threads[t], NULL, subtraction, (void *)&numbers[t]);
            break;
        case 2:
            pthread_create(&threads[t], NULL, multiplication, (void *)&numbers[t]);
            break;
        case 3:
            pthread_create(&threads[t], NULL, division, (void *)&numbers[t]);
            break;
        default:
            fprintf(stderr, "Error\n");
            exit(1);
        }
    }
    printf("\n");
    pthread_exit(0);
}