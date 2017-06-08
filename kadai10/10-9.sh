#!/bin/bash

if [ $# -ne 1 ]; then
    echo "usage: ./10-9.sh [DIR_PATH]"
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

for f in `find "$DIRPATH" -name "*.*"`; do
    echo $f
    #echo ${f%.*}
    #echo ${f##*.}
    n="${f%.*}-backup"
    e="${f##*.}"
    ne="${n}.${e}"
    echo $ne
    cp $f $ne
done

echo "done."
