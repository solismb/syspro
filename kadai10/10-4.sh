#!/bin/bash

edit_and_compile() {
    vi $f
    gcc $f
    export COMPILE_STATUS=$?
}

execute() {
    if [ $COMPILE_STATUS -eq 0 ]; then
        ./a.out
    else
        echo -e "\n[10-4.sh info]: compile error."
    fi
}

if [ $# -eq 1 ]; then
    f=$1
else
    echo "usage: ./10-4.sh [file].c"
    exit
fi

if [ ${f##*.} = "c" ]; then
    edit_and_compile
    execute
else
    echo "not a C file."
fi  

while :
do
    echo -n -e "\nvi = [v], a.out = [a], exit = [e] [v/a/e]: "
    read key
    case "$key" in
        "v" ) edit_and_compile
              execute ;;
        "a" ) execute ;;
        "e" ) break ;;
        * ) echo -e "\nplease input [v], [a] or [e]" ;;
    esac
done    
