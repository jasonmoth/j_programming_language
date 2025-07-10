#!/bin/sh

# Update repo
git pull origin master

# Compile the compiler
gcc j_compiler.c -o j_compiler

# Run compiler on all .j test files
for file in ./test_programs/*.j; do
    echo "Running j_compiler on $file..."
    ./j_compiler "$file"
done
