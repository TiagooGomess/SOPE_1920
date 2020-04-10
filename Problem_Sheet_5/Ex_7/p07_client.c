#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>

typedef struct {
    int firstNum;
    int secondNum;
} Nums;

int main(void) {
    int fd;
    Nums numbers;

    do {
        fd=open("/tmp/requests",O_WRONLY);
        sleep(1);
        printf("\nWaiting for the server ...\n");
    } while (fd == -1);

    printf("\n-------------------------------------------\n");

    do {
        printf("\nPrimeiro número: ");
        if (scanf("%d", &numbers.firstNum) != 1) {
            fprintf(stderr, "Error reading the first number\n");
            exit(3);
        }
        printf("Segundo número: ");
        if (scanf("%d", &numbers.secondNum) != 1) {
            fprintf(stderr, "Error reading the second number\n");
            exit(4);
        }
        write(fd,&numbers,sizeof(Nums));
        printf("-------------------------------------------");
    } while (numbers.firstNum != 0 || numbers.secondNum != 0);
    
    printf("\n\n");
    close(fd);
    return 0;
}
