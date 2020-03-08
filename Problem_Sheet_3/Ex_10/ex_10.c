#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[]) {
    pid_t pid;
    int status, fd;
    if (argc != 2 && argc != 3) {
        printf("usage: %s dirname\nOR\nusage: %s dirname filename\n",argv[0], argv[0]);
        exit(1);
    }
    if (argc == 3) {
        fd = open(argv[2],O_CREAT|O_EXCL|O_TRUNC|O_WRONLY|O_SYNC,0600);
        dup2(fd,STDOUT_FILENO);
    }
    pid=fork();
    if (pid > 0) {
        printf("My child is going to execute command \"ls -laR %s\"\n", argv[1]);
        wait(&status);
    }
    else if (pid == 0){
        execlp("ls", "ls", "-laR", argv[1], NULL);
        printf("Command not executed !\n");
        exit(1);
    }
    exit(0);
} 