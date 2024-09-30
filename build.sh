#!/bin/bash

rm build
mkdir build

# Define common compilation flags and libraries
CFLAGS=`pkg-config --cflags gtk+-3.0 gdk-pixbuf-2.0`
LIBS=`pkg-config --libs gtk+-3.0 gdk-pixbuf-2.0`

# Compile and move each source file
for file in c-panel.c c-menu.c c-settings.c c-start.c; do
  gcc -o "${file%.*}" "$file" $CFLAGS $LIBS
  if [ $? -ne 0 ]; then
    echo "Error: Compilation of $file failed!"
    exit 1
  fi
  mv "${file%.*}" build/
done