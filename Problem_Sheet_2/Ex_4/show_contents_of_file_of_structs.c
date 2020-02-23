#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define NAME_SIZE 50
#define GRADE_SIZE 8

typedef struct Student {
    char name[NAME_SIZE+1];
    int grade;
} Student;

// https://www.sanfoundry.com/c-program-integer-to-string-vice-versa/
void tostring(char str[], int num) {
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0) {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++) {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

/* Para correr este programa, precisamos primeiro de correr a alinea_b, que irá criar um ficheiro,
   ficheiro esse que terá que ser passado como parâmetro neste programa. */

int main(int argc, char* argv[]) {

    int fd1;
    char grade[GRADE_SIZE+1];
    Student student;

    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {  /* Erro ao abrir o ficheiro <file> */
        perror(argv[1]);
        close(fd1);
        return 2;
    }

    while(read(fd1, &student, sizeof(student))) {
        write(STDOUT_FILENO, "\nName: ", 7);
        write(STDOUT_FILENO, student.name, strlen(student.name));
        write(STDOUT_FILENO, "\nGrade: ", 8);
        tostring(grade, student.grade);
        write(STDOUT_FILENO, grade, strlen(grade));
        write(STDOUT_FILENO, "\n", 1);
    }
    
    close(fd1);

    return 0;
}
