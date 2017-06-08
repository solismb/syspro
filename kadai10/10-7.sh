#!/bin/sh

#for f in `find -type f -name "*.c"`; do
#    p=$((p + `grep printf "$f" | wc -l`))
#    s=$((s + `grep scanf "$f" | wc -l`))
#done

#echo "printf: $p"
#echo "scanf : $s"

echo "printf: `find -type f -name "*.c" | xargs cat | grep printf | wc -l`"
echo "scanf: `find -type f -name "*.c" | xargs cat | grep scanf | wc -l`"
