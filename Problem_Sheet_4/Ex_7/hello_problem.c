#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    printf("Hello! I'm going to sleep for 5 seconds!\n");
    sleep(5);
    printf("I'm back!\n");
    exit(1);
}