#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 512

int main(int argc, char* argv[]) {
    int fd1, nr, nw;
    unsigned char buffer[BUFFER_SIZE];

    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }
    fd1 = open(argv[1],O_RDONLY); /* Abertura do ficheiro só para leitura */
    if (fd1 == -1) {  /* Erro ao abrir o ficheiro <source> */
        perror(argv[1]);
        return 2;
    }

    while((nr = read(fd1, buffer, BUFFER_SIZE)) > 0) {
        if ((nw = write(STDOUT_FILENO, buffer, nr)) <= 0 || nw != nr) {
            perror(argv[1]);
            close(fd1);
            return 3;
        }
    }
    close(fd1);
    return 0;
}
