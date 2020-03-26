#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

typedef struct {
    int sum;
    int difference;
    int multiplication;
    double division;
    int valid;
} Results;

int main(void) {
    int fd1[2], fd2[2];
    pid_t pid;
    if (pipe(fd1) != 0) {
        fprintf(stderr, "Error while creating the first pipe\n");
        exit(1);
    }
    if (pipe(fd2) != 0) {
        fprintf(stderr, "Error while creating the second pipe\n");
        exit(2);
    }
    pid = fork();
    if (pid > 0) { // pai
        int nums[2];
        printf("\n--------------------------PAI--------------------------\n");
        printf("\nPrimeiro número: ");
        if (scanf("%d", &nums[0]) != 1) {
            fprintf(stderr, "Error reading the first number\n");
            exit(3);
        }
        printf("\nSegundo número: ");
        if (scanf("%d", &nums[1]) != 1) {
            fprintf(stderr, "Error reading the second number\n");
            exit(4);
        }
        close(fd1[READ]);
        write(fd1[WRITE], nums, 2*sizeof(int));
        close(fd1[WRITE]);

        Results results;
        close(fd2[WRITE]);
        read(fd2[READ], &results, sizeof(Results));
        printf("\n--------------------------PAI--------------------------\n");
        printf("\nSoma: %d\n", results.sum);
        printf("Diferença: %d\n", results.difference);
        printf("Multiplicação: %d\n", results.multiplication);
        if (!results.valid) {
            fprintf(stderr, "Operação de divisão por 0 é inválida!\n");
            exit(5);
        }
        else {
            printf("Divisão: %f\n", results.division);
        }
    }
    else if (pid == 0) { // filho
        int nums[2];
        Results results;
        close(fd1[WRITE]);
        read(fd1[READ], nums, 2*sizeof(int));
        printf("\n--------------------------FILHO--------------------------\n");
        results.sum = nums[0] + nums[1];
        results.difference = nums[0] - nums[1];
        results.multiplication = nums[0] * nums[1];
        if (nums[1] == 0) {
            results.valid = 0;
        }
        else {
            results.valid = 1;
            results.division = (double) nums[0] / nums[1];
        }
        close(fd2[READ]);
        write(fd2[WRITE], &results, sizeof(Results));
        close(fd2[WRITE]);
        
    }
    else {
        fprintf(stderr, "Error!\n");
        exit(6);
    }

    exit(0);
}