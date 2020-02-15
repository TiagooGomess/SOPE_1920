#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    const char* user = getenv("USER");
    printf("Hello %s\n",user);
    return 0;
}