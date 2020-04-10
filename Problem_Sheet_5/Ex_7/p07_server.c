#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

typedef struct {
    int firstNum;
    int secondNum;
} Nums;

int main(void) {
    int fd;
    Nums numbers;

    if (mkfifo("/tmp/requests",0660) < 0) {
        if (errno == EEXIST)
            printf("FIFO '/tmp/requests' already exists\n");
        else printf("Can't create FIFO\n");
        exit(1);
    }

    fd = open("/tmp/requests",O_RDONLY);

    printf("\n-------------------------------------------\n");

    do {
        read(fd,&numbers,sizeof(Nums));
        if (numbers.firstNum != 0 || numbers.secondNum != 0) {
            printf("\nSoma: %d\n", numbers.firstNum + numbers.secondNum);
            printf("Diferença: %d\n", numbers.firstNum - numbers.secondNum);
            printf("Multiplicação: %d\n", numbers.firstNum * numbers.secondNum);
            if (numbers.secondNum == 0) {
                fprintf(stderr, "Operação de divisão por 0 é inválida!\n");
                exit(1);
            }
            else {
                printf("Divisão: %f\n", (double) numbers.firstNum / numbers.secondNum);
            }
            printf("-------------------------------------------");
        }
    } while (numbers.firstNum != 0 || numbers.secondNum != 0);
    
    close(fd);
    if (unlink("/tmp/requests") < 0)
        printf("Error when destroying FIFO '/tmp/requests'\n");
    printf("\n\n");
    exit(0);
}
