#!/bin/bash

if [ $# -ne 1 ]; then
    echo "usage: ./10-8.sh [DIR_PATH]"
    exit
fi

DIRPATH=$1

#for file in ${DIRPATH}*.c; do
#    echo ${file}
#done

if [ ! -d "$DIRPATH" ]; then
    echo "it is not a directory."
    exit
fi

for f in `find "$DIRPATH" -name "*.c"`; do
    b="${f}-backup"
    cp $f $b
done

echo "done."
