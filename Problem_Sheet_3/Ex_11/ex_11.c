#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAX_LEN 100
#define MAX_COMMANDS 20

int getCommand(char* array[MAX_COMMANDS]) {
    int numCmd = 0;
    char cmd[MAX_LEN];
    printf("minish > ");
    fgets(cmd , sizeof(cmd), stdin);   
    char* tok = strtok(cmd, " ");
    array[0] = tok;
    numCmd++;
    for (int i = 1; i < MAX_COMMANDS; i++) {
        tok = strtok(NULL, " ");
        if (tok == NULL) {
            array[i] = NULL;
            array[i-1][strlen(array[i-1])-1] = '\0';
            break;
        }
        array[i] = tok;
        numCmd++;
    }
    return numCmd;
}

// verifica se os dois últimos comandos são "-o filename"
int verifyOutput(char* array[MAX_COMMANDS], int numCmd, char** filename) {
    if (numCmd < 3)
        return 0;
    if (strcmp(array[numCmd-2], "-o") == 0) {
        *filename = array[numCmd-1];
        return 1;
    }
    return 0;
}

int main(void) {
    int status, pid, numCmd = 0, out = dup(STDOUT_FILENO), fd, toFile = 0;
    char* cmd_array[MAX_COMMANDS];
    char* filename;
    numCmd = getCommand(cmd_array);
    if (verifyOutput(cmd_array, numCmd, &filename)) {
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0600);
        dup2(fd, STDOUT_FILENO);
        toFile = 1;
    }

    while (strcmp(cmd_array[0],"quit") != 0) {
        pid=fork();
        if (pid>0) {
            wait(&status);
            if (!toFile)
                dup2(out, STDOUT_FILENO);
            numCmd = getCommand(cmd_array);
            if (verifyOutput(cmd_array, numCmd, &filename)) {
                fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0600);
                dup2(fd, STDOUT_FILENO);
                toFile = 1;
            }
            else {
                dup2(out, STDOUT_FILENO);
                toFile = 0;
            }
            
        }
        else {
            if (!toFile) {
                execvp(cmd_array[0],cmd_array);
            }
                
            else {
                cmd_array[numCmd-2] = NULL;
                cmd_array[numCmd-1] = NULL;
                execvp(cmd_array[0],cmd_array);
            }
                
            printf("Command not found !!!\n");
            exit(1);
        } 
    }
    return 0;
}