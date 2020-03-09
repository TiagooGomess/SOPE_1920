#include <stdio.h>
#include <unistd.h>

int global=1;

int main(void) {
    int local = 2;
    if(fork() > 0) {
        printf("PROCESSO-PAI:\n");
        printf("PID = %d; PPID = %d\n", getpid(), getppid());
        printf("-----------------------\n");
        global++;
        local--;
    } else {
        printf("PROCESSO-FILHO:\n");
        printf("PID = %d; PPID = %d\n", getpid(), getppid());
        printf("-----------------------\n");
        global--;
        local++;
    }
    printf("PID = %d - global = %d ; local = %d\n", getpid(), global, local);
    return 0;
}

/*

a)
--> Output do programa:

PROCESSO-PAI:
PID = 4830; PPID = 3552
-----------------------
PID = 4830 - global = 2 ; local = 1
PROCESSO-FILHO:
PID = 4831; PPID = 4830
-----------------------
PID = 4831 - global = 0 ; local = 3

--> O processo pai é executado primeiro;
--> O PID do processo filho é igual ao PID do processo pai acrescido de uma unidade;
--> Quando se faz uma chamada getppid() no processo filho é retornado o PID do processo pai, como seria de esperar.

b)
Quando executamos o programa várias vezes, os valores dos PID dos processos mudam (aumentam sempre).


*/
