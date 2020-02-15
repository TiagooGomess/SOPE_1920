#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    clock_t start, end;
    struct tms t;
    long ticks;

    start = times(&t);
    ticks = sysconf(_SC_CLK_TCK);

    srand(time(0));
    int number = atoi(argv[2]);
    int n = -1;
    int i = 0;
    while (n != number) {
        n = rand() % (atoi(argv[1]));
        printf("i: %d\t\tn: %d\n",i,n);
        i++;
    }

    end = times(&t);

    printf("\n\nReal time: %4.2f s\n", (double)(end-start)/ticks);
    printf("User time: %4.2f s\n", (double)t.tms_utime/ticks);
    printf("System time: %4.2f s\n", (double)t.tms_stime/ticks);

    return 0;
}