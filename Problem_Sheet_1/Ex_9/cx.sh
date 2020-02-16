#!/bin/bash

if [ "$1" != "" ]; then
    parameter="$1"
    filename="$parameter.c"
    echo
    echo "... Compiling and executing $filename ..."
    rm $parameter -f
    rm *.o -f
    echo
    gcc -Wall -o "$parameter" "$filename"
    if [ "$?" != 0 ]; then
	echo "COMPILATION ERROR!"
    else
	./$parameter
    fi
    
else
    echo "The name of the file cannot be empty"
fi


# If "Permission denied":
# chmod u+x cx.sh

# Example of execution (assuming there is a file hello.c on the same directory of the program). At the terminal:
# ./cx hello

