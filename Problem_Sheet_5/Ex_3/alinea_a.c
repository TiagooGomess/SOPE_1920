#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define READ 0
#define WRITE 1

#define MAX_NAMES 1024
#define MAX_LEN_NAME 256

int compareNames(const void * a, const void *b){
     return strcmp(*(char **)a,*(char**) b); 
 }

int main(int argc, char* argv[]) {
    pid_t pid;
    int pi[2];
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    if (pipe(pi) != 0) {
        fprintf(stderr, "Error while creating the first pipe\n");
        exit(3);
    }
    pid = fork();
    if (pid > 0) { // pai
        FILE* fp;
        char buffer[MAX_LEN_NAME];
        close(pi[READ]);
        dup2(pi[WRITE], STDOUT_FILENO);
        if ((fp = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "Error opening the file \"%s\"!\n", argv[1]);
            exit(2);
        }
        while (fgets(buffer, sizeof(buffer), fp)) {
            printf("%s", buffer);
        }
        fclose(fp);
    }
    else if (pid == 0) { // filho
        char* buffer = (char*)calloc(MAX_LEN_NAME, sizeof(char));
        char* names[MAX_NAMES];
        int i;
        close(pi[WRITE]); 
        dup2(pi[READ], STDIN_FILENO);        
        while (fgets(buffer, MAX_LEN_NAME, stdin)) {
            names[i] = (char*)calloc(strlen(buffer), sizeof(char));
            strcpy(names[i], buffer);
            i++;
        }
        close(pi[READ]);
        qsort(names, i, sizeof(char*), compareNames);
        for (int j = 0; j < i; j++) {
            printf("%s", names[j]);
        }

    }
    else {
        fprintf(stderr, "Error while forking!\n");
        exit(4);
    }
    
    exit(0);
}