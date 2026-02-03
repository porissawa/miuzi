#!/bin/sh

if test $1 = "build"; then
    gcc -o build/amdf main.c wav.c -lm -Wall -Wextra
elif test $1 = "run"; then
    ./build/amdf $2
else
    echo "options are build | run [path]"
fi