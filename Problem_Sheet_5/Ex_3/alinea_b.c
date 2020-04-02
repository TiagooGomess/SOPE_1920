#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1

int main(int argc, char* argv[]) {
    pid_t pid;
    int fd[2], filedesc;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    if (pipe(fd) != 0) {
        fprintf(stderr, "Error while creating the first pipe\n");
        exit(2);
    }
    pid = fork();
    if (pid > 0) { // pai
        close(fd[READ]);
        if ((filedesc = open(argv[1], O_RDONLY)) < 0) {
            fprintf(stderr, "Error while opening the file\n");
        }
        dup2(fd[WRITE], STDOUT_FILENO);
        execlp("cat", "cat", argv[1], NULL);
        fprintf(stderr, "Error while executing cat\n");
        exit(3);
    }
    else if (pid == 0) { // filho
        close(fd[WRITE]);
        dup2(fd[READ], STDIN_FILENO);
        execlp("sort", "sort", NULL);
        fprintf(stderr, "Error while executing sort\n");
        exit(4);
    }
    else {
        fprintf(stderr, "Error while forking!\n");
        exit(5);
    }
    
    exit(0);
}