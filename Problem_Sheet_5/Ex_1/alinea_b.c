#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

typedef struct {
    int num1;
    int num2;
} Nums;

int main(void) {
    int fd[2];
    pid_t pid;
    pipe(fd);
    pid = fork();
    if (pid > 0) { // pai
        Nums nums;
        printf("\n--------------------------PAI--------------------------\n");
        printf("\nPrimeiro número: ");
        if (scanf("%d", &nums.num1) != 1) {
            fprintf(stderr, "Error reading the first number\n");
            exit(1);
        }
        printf("\nSegundo número: ");
        if (scanf("%d", &nums.num2) != 1) {
            fprintf(stderr, "Error reading the second number\n");
            exit(2);
        }
        close(fd[READ]);
        write(fd[WRITE], &nums, sizeof(Nums));
        close(fd[WRITE]);
    }
    else if (pid == 0) { // filho
        Nums nums;
        close(fd[WRITE]);
        read(fd[READ], &nums, 2*sizeof(int));
        printf("\n--------------------------FILHO--------------------------\n");
        printf("\nSoma: %d\n", nums.num1 + nums.num2);
        printf("Diferença: %d\n", nums.num1 - nums.num2);
        printf("Multiplicação: %d\n", nums.num1 * nums.num2);
        if (nums.num2 == 0) {
            fprintf(stderr, "Operação de divisão por 0 é inválida!\n");
            exit(3);
        }
        printf("Divisão: %f\n", (double) nums.num1 / nums.num2);
    }
    else {
        fprintf(stderr, "Error!\n");
        exit(1);
    }

    exit(0);
}