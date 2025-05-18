#!/bin/bash
# filepath: /home/manish/rnd/misc/misc/clean.sh

# Remove the build directory
if [ -d "build" ]; then
    rm -rf build
    echo "Build directory removed."
else
    echo "No build directory found."
fi