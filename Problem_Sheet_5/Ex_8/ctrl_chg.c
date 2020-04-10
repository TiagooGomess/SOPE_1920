#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <errno.h>
#include <string.h>

#define USER_MAX_LEN 50
#define ONE_MINUTE 60*1000*1000 // number of microseconds in one minute

int main(void) {
    int fd, microSeconds = 0, readReturnValue = 1;
    char username[USER_MAX_LEN];

    unlink("/tmp/fifo_chg");

    if (mkfifo("/tmp/fifo_chg", 0660) < 0) {
        if (errno == EEXIST)
            fprintf(stderr, "FIFO '/tmp/fifo_chg' already exists\n");
        else
            fprintf(stderr, "Can't create FIFO\n");
        exit(1);
    }

    while (microSeconds < ONE_MINUTE) {
        fd = open("/tmp/fifo_chg", O_RDONLY | O_NONBLOCK);
        readReturnValue = read(fd, username, USER_MAX_LEN);
        if (readReturnValue > 0)
            printf("\nCHEGOU %s\n", username);
        usleep(50000);
        microSeconds += 50000;
    }
    
    close(fd);
    if (unlink("/tmp/fifo_chg") < 0)
        printf("Error when destroying FIFO '/tmp/fifo_chg'\n");

    exit(0);
}