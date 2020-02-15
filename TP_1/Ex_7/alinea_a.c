#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func1() {
    printf("Executing exit handler 1\n");
}

void func2() {
    printf("Executing exit handler 2\n");
}

int main(int argc, char* argv[]) {

    if (strcmp(argv[1],"arg1") == 0) {
        atexit(func1);
    }
    else if (strcmp(argv[1],"arg2") == 0) {
        atexit(func2);
    }
    else {
        printf("atexit handler not used\n");
    }

    printf("Main done!\n");
    return 0;
}