#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main(void) {
    int fd[2];
    pid_t pid;
    pipe(fd);
    pid = fork();
    if (pid > 0) { // pai
        int nums[2];
        printf("\n--------------------------PAI--------------------------\n");
        printf("\nPrimeiro número: ");
        if (scanf("%d", &nums[0]) != 1) {
            fprintf(stderr, "Error reading the first number\n");
            exit(1);
        }
        printf("\nSegundo número: ");
        if (scanf("%d", &nums[1]) != 1) {
            fprintf(stderr, "Error reading the second number\n");
            exit(2);
        }
        close(fd[READ]);
        write(fd[WRITE], nums, 2*sizeof(int));
        close(fd[WRITE]);
    }
    else if (pid == 0) { // filho
        int nums[2];
        close(fd[WRITE]);
        read(fd[READ], nums, 2*sizeof(int));
        printf("\n--------------------------FILHO--------------------------\n");
        printf("\nSoma: %d\n", nums[0] + nums[1]);
        printf("Diferença: %d\n", nums[0] - nums[1]);
        printf("Multiplicação: %d\n", nums[0] * nums[1]);
        if (nums[1] == 0) {
            fprintf(stderr, "Operação de divisão por 0 é inválida!\n");
            exit(3);
        }
        printf("Divisão: %f\n", (double) nums[0] / nums[1]);
    }
    else {
        fprintf(stderr, "Error!\n");
        exit(1);
    }

    exit(0);
}