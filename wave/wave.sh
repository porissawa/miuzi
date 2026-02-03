#!/bin/sh

if test $1 = "build"; then
    gcc -o build/wav_gen main.c wav.c -lm -Wall -Wextra
elif test $1 = "run"; then
    ./build/wav_gen
else
    echo "options are build | run"
fi