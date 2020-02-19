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

    if (argc != 3) {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }
    fd1 = open(argv[1],O_RDONLY); /* Abertura do ficheiro só para leitura */
    if (fd1 == -1) {  /* Erro ao abrir o ficheiro <source> */
        perror(argv[1]);
        return 2;
    }
    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, MODE); /* Abertura só para escrita; 
                                                                 criar o ficheiro se ele não existir; 
                                                                 acrescentar no fim do ficheiro */
    if (fd2 == -1) {  /* Erro ao abrir o ficheiro <destination> */
        perror(argv[2]);
        close(fd1);
        return 3;
    }
    while((nr = read(fd1, buffer, BUFFER_SIZE)) > 0) {
        if ((nw = write(fd2, buffer, nr)) <= 0 || nw != nr) {
            perror(argv[2]);
            close(fd1);
            close(fd2);
            return 4;
        }
    }
    close(fd1);
    close(fd2);
    return 0;
}