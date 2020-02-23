#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define NAME_SIZE 50
#define GRADE_SIZE 8
#define CHOICE_SIZE 4
#define MODE S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH /* Permissões associadas ao ficheiro
                                                                que será criado */

typedef struct Student {
    char name[NAME_SIZE+1];
    int grade;
} Student;

int main(int argc, char* argv[]) {

    int i = 0, fd1, grade_int;
    char name[NAME_SIZE+1], grade[GRADE_SIZE+1], choice[CHOICE_SIZE+1], ch;

    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    fd1 = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, MODE); /* Abertura só para escrita; 
                                                                criar o ficheiro se ele não existir; 
                                                                acrescentar no fim do ficheiro */
    if (fd1 == -1) {  /* Erro ao abrir o ficheiro <destination_file> */
        perror(argv[1]);
        close(fd1);
        return 2;
    }

    while (1) {

        Student student;

        /* Clearing the buffers */
        memset(name, 0, NAME_SIZE);
        memset(grade, 0, GRADE_SIZE);
        memset(choice, 0, CHOICE_SIZE);

        write(STDOUT_FILENO, "\nName: ", 7); /* 7 caracteres -> 7 bytes */

        i = 0;
        while (i < NAME_SIZE && read(STDIN_FILENO, &ch, 1) && ch != '\n') {
            name[i++] = ch;
        }
        name[i] = 0;

        strcpy(student.name, name);

        write(STDOUT_FILENO, "\nGrade: ", 8);
        i = 0;
        while (i < GRADE_SIZE && read(STDIN_FILENO, &ch, 1) && ch != '\n') {
            grade[i++] = ch;
        }
        grade[i] = 0;

        if ((grade_int = atoi(grade)) == 0) {
            write(STDERR_FILENO, "\nInvalid Grade\n", 15);
            close(fd1);
            return 3;
        }

        student.grade = grade_int;

        write(fd1, &student, sizeof(student));

        write(STDOUT_FILENO, "\nDo you want to enter the information of more students? (yes / no) ", 67);
        i = 0;
        while (i < CHOICE_SIZE && read(STDIN_FILENO, &ch, 1) && ch != '\n') {
            choice[i++] = ch;
        }
        choice[i] = 0;

        if (strcmp(choice, "no") == 0 || strcmp(choice, "n") == 0)
            break;

        else if (strcmp(choice, "yes") != 0 && strcmp(choice, "y") != 0) {
            write(STDERR_FILENO, "\nChoice not valid!\n", 19);
            close(fd1);
            return 3;
        }   
    }
    close(fd1);

    return 0;
}
