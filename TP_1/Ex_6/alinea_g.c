// PROGRAMA p6a.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define BUF_LENGTH 256

int main(int argc, char* argv[]) {
    FILE *src, *dst;
    char buf[BUF_LENGTH];
    if ( ( src = fopen( argv[1], "r" ) ) == NULL ) {
        printf("errno: %d\n",errno);
        exit(1);
    }
    if ( ( dst = fopen( argv[2], "w" ) ) == NULL ) {
        printf("errno: %d\n",errno);
        exit(2);
    }
    while( ( fgets( buf, BUF_LENGTH, src ) ) != NULL ) {
        fputs( buf, dst );
    }
    fclose( src );
    fclose( dst );
    exit(0); // zero é geralmente indicativo de "sucesso"
}

/*
--> Example of compilation and execution commands (assuming that there is a file named infile.txt on the same path of the program):

gcc -o alinea_g alinea_g.c -Wall
./alinea_g infile.txt outfile.txt


--> When we execute the program without arguments (./alinea_g), is printed on the screen:

errno: 14

--> This error means "Invalid file descriptor".
*/
