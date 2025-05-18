#!/bin/bash

set -e  # Exit immediately if a command exits with a non-zero status
set -x  # Print commands and their arguments as they are executed

# Install required packages
sudo apt update
sudo apt install -y \
    build-essential \
    cmake \
    git \
    libgtest-dev

# Build and install Google Test
if [ ! -f "/usr/lib/libgtest.a" ]; then
    cd /usr/src/gtest
    sudo cmake .
    sudo make
    sudo cp lib/*.a /usr/lib
    cd -
fi
