#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 512
#define MODE S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH /* Permissões associadas ao ficheiro
                                                                que será criado */

int main(int argc, char* argv[]) {
    int fd1, fd2, nr, nw;
    unsigned char buffer[BUFFER_SIZE];

    if (argc != 2 && argc != 3) {
        printf("Usage: %s <file>\nor\nUsage: %s <file> <destination_file>\n", argv[0], argv[0]);
        return 1;
    }
    fd1 = open(argv[1],O_RDONLY); /* Abertura do ficheiro só para leitura */
    if (fd1 == -1) {  /* Erro ao abrir o ficheiro <file> */
        perror(argv[1]);
        return 2;
    }

    if (argc == 2) {
        while((nr = read(fd1, buffer, BUFFER_SIZE)) > 0) {
            if ((nw = write(STDOUT_FILENO, buffer, nr)) <= 0 || nw != nr) {
                perror(argv[1]);
                close(fd1);
                return 3;
            }
        }
        close(fd1); 
    }

    if (argc == 3) {
        fd2 = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, MODE); /* Abertura só para escrita; 
                                                                 criar o ficheiro se ele não existir; 
                                                                 acrescentar no fim do ficheiro */
        if (fd2 == -1) {  /* Erro ao abrir o ficheiro <destination_file> */
            perror(argv[2]);
            close(fd1);
            return 4;
        }
        if (dup2(fd2, STDOUT_FILENO) == -1)
            return 5;
        while((nr = read(fd1, buffer, BUFFER_SIZE)) > 0) {
            if ((nw = write(STDOUT_FILENO, buffer, nr)) <= 0 || nw != nr) {
                perror(argv[1]);
                close(fd1);
                close(fd2);
                return 6;
            }
        }
        close(fd1);
        close(fd2);
    }

    return 0;
}
