#!/bin/bash
# filepath: /home/manish/rnd/misc/misc/build.sh

set -e  # Exit immediately if a command exits with a non-zero status

# Create build directories for Debug and Release
mkdir -p build/debug build/release

# Build Debug version
echo "Building Debug version..."
cd build/debug
cmake -DCMAKE_BUILD_TYPE=Debug ../..
make
cd ../..

# Build Release version
echo "Building Release version..."
cd build/release
cmake -DCMAKE_BUILD_TYPE=Release ../..
make
cd ../..

echo "Build completed successfully for both Debug and Release versions."