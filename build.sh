#!/bin/bash

# Specify the name of your C source file
SOURCE_FILE="panel.c"

# Compile the C program using GCC
gcc -o panel $SOURCE_FILE \
    `pkg-config --cflags gtk+-3.0 gdk-pixbuf-2.0` \
    `pkg-config --libs gtk+-3.0 gdk-pixbuf-2.0`

# Check if the compilation was successful
if [ $? -ne 0 ]; then
  echo "Error: Compilation failed!"
  exit 1
fi

# Move compiled programs to build dir
mv panel build/