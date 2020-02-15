#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    srand(time(0));
    int number = atoi(argv[2]);
    int n = -1;
    int i = 0;
    while (n != number) {
        n = rand() % (atoi(argv[1]));
        printf("i: %d\t\tn: %d\n",i,n);
        i++;
    }

    return 0;
}