#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func1() {
    printf("Executing exit handler 1\n");
    //exit(1); /* The handler is installed, even though there is an exit() */
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
    
    atexit(func1);
    atexit(func1); /* It's possible to install a handler more than once */
    
    //abort(); /* The program stops here and the exit handers are not installed */
    
    printf("Main done!\n");
    return 0;
}