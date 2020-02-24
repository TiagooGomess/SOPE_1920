#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
  int fd;
  char *text1="AAAAA";
  char *text2="BBBBB";

  if ((fd = open("f1.txt",O_CREAT|O_WRONLY|O_SYNC|O_APPEND,0600)) < 0) {
    perror("f1.txt");
    return 1;
  }
  getchar();
  if (write(fd,text1,5) < 0) {
    perror("Error");
    return 2;
  }
  getchar();
  if (write(fd,text2,5) < 0) {
    perror("Error");
    return 3;
  }
  close(fd);
  return 0;
}

