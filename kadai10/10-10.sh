#!/bin/bash

if [ $# -ne 1 ]; then
    echo "usage: ./10-10.sh [DIR_PATH]"
    exit
fi

DIRPATH=$1

if [ ! -d "$DIRPATH" ]; then
    echo "it is not a directory."
    exit
fi

d=`date '+%y%m%d'`

for f in `find "$DIRPATH" -name "*.*"`; do
    cp "$f" "${f%.*}-${d}.${f##*.}"
done

echo "done."
