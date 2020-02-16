#!/bin/bash

COUNTER=1
FOLDER_NAME=""
while [ $COUNTER -lt 13 ]; do
    if [ $COUNTER -lt 10 ]; then
	FOLDER_NAME="aula0$COUNTER"
    else
	FOLDER_NAME="aula$COUNTER"
    fi
    mkdir $FOLDER_NAME
    let COUNTER=COUNTER+1
done

