#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    printf("Hello! I'm going to sleep for 10 seconds!\n");
    sleep(10);
    printf("I'm back!\n");
    exit(0);
}