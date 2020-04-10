#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int fd;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s username\n", argv[0]);
        exit(1);
    }

    fd = open("/tmp/fifo_chg", O_WRONLY);
    while (fd == -1) {
        printf("\nWaiting for the server ...\n");
        sleep(2);
        fd = open("/tmp/fifo_chg", O_WRONLY);
    }

    write(fd, argv[1], strlen(argv[1])+1);

    close(fd);
    exit(0);
}