#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_array(char* array) {
    int i = 0;
    while (array[i] != '\0') {
        printf("i:%d\t\t%c\n",i,array[i]);
        i++;
    }
}

int main(int argc, char* argv[]) {
    char command[1001];
    printf("Enter the command: ");
    scanf("%1000[^\n]", command);
    char* word = strtok(command, " ");
    char array[1000];
    int itr = 0;
    while (word != NULL) {
        for (int i = 0; i < strlen(word); i++) {
            array[itr] = word[i];
            itr++;
        }
        word = strtok(NULL," ");
    }
    array[itr] = '\0';
    print_array(array);
    return 0;
}