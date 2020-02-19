#include <stdio.h>
#include <stdlib.h>

#define BUF_LENGTH 256

int main(int argc, char* argv[]) {
    FILE *src, *dst;
    char buf[BUF_LENGTH];
    if (argc != 3) {
        fprintf( stderr, "Usage: %s source_file destination_file\n", argv[0]);
        exit(1);
    }
    if ( ( src = fopen( argv[1], "r" ) ) == NULL ) {
        exit(1);
    }
    if ( ( dst = fopen( argv[2], "w" ) ) == NULL ) {
        exit(2);
    }
    while( ( fgets( buf, BUF_LENGTH, src ) ) != NULL ) {
        fputs( buf, dst );
    }
    fclose( src );
    fclose( dst );
    exit(0);
}