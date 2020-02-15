#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    const char* path = getenv("PATH");
    printf("PATH: %s\n", path);
    return 0;
}