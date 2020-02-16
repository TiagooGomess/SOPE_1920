#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char command[1001];
    printf("Enter the command: ");
    scanf("%1000[^\n]", command);

    char* word = strtok(command, ";|");

    while (word != NULL) {
        for (int i = 0; i < strlen(word); i++) {
            printf("%c ",word[i]);
        }
        printf("\n");
        word = strtok(NULL,";|");
    }
    
    printf("\n");

    return 0;
}