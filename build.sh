#!/bin/bash

# Compile source files
gcc -o main ./lib/huffman.c ./lib/tree.c ./lib/pq.c main.c -Wall -Wextra -std=c11 -g

# Check compilation success
if [ $? -eq 0 ]; then
    echo "Build successful. Executable 'main' created."
else
    echo "Build failed."
fi
