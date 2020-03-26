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
        char nums[2][10];
        printf("\n--------------------------PAI--------------------------\n");
        printf("\nPrimeiro número: ");
        if (scanf("%s", nums[0]) != 1) {
            fprintf(stderr, "Error reading the first number\n");
            exit(1);
        }
        printf("\nSegundo número: ");
        if (scanf("%s", nums[1]) != 1) {
            fprintf(stderr, "Error reading the second number\n");
            exit(2);
        }
        close(fd[READ]);
        write(fd[WRITE], nums, 2*sizeof(char[10]));
        close(fd[WRITE]);
    }
    else if (pid == 0) { // filho
        char nums[2][10];
        int num1, num2;
        close(fd[WRITE]);
        read(fd[READ], nums, 2*sizeof(char[10]));
        printf("\n--------------------------FILHO--------------------------\n\n");
        if (sscanf(nums[0], "%d", &num1) != 1) {
            fprintf(stderr, "The first number is not valid!\n");
            exit(3);
        }
        if (sscanf(nums[1], "%d", &num2) != 1) {
            fprintf(stderr, "The second number is not valid!\n");
            exit(4);
        }
        printf("Soma: %d\n", num1 + num2);
        printf("Diferença: %d\n", num1 - num2);
        printf("Multiplicação: %d\n", num1 * num2);
        if (num2 == 0) {
            fprintf(stderr, "Operação de divisão por 0 é inválida!\n");
            exit(3);
        }
        printf("Divisão: %f\n", (double) num1 / num2);
    }
    else {
        fprintf(stderr, "Error!\n");
        exit(1);
    }

    exit(0);
}