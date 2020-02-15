#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    /* 
    --> At the terminal, enter the command:
    export USER_NAME="nome completo" 
    --> To see the value of the variable in the terminal, enter the command:
    $echo USER_NAME 
    */
    const char* user_name = getenv("USER_NAME"); 
    printf("Hello %s\n",user_name);
    return 0;
}