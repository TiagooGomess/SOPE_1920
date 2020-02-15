#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int number_of_times = atoi(argv[1]);
    for(int i = 0; i < number_of_times; i++) {
        for (int j = 2; j < argc; j++) {
            printf("%s ",argv[j]);
        }
        printf("\n");
    }
    return 0;
}