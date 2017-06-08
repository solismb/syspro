#!/bin/bash

if [ $# -eq 1 ]; then
    f=$1
else
    echo "usage: ./10-3.sh [file].c"
    exit
fi

if [ ${f##*.} = "c" ]; then
    vi $f
    gcc $f
    if [ $? -eq 0 ]; then
        ./a.out
    else
        echo "[10-3.sh info]: compile error."
    fi
else
    echo "not a C file."
fi
