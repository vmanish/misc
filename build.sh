#!/bin/sh
# filepath: /home/manish/rnd/misc/misc/build.sh

set -e  # Exit immediately if a command exits with a non-zero status

# Remove the build directory
if [ -d "build" ]; then
    rm -rf build
    echo "Build directory removed."
else
    echo "No build directory found."
fi

# Create build directories for Debug and Release
mkdir -p build/debug build/release

# Build Debug version
echo "Building Debug version..."
cd build/debug
cmake -DCMAKE_BUILD_TYPE=Debug ../..
make
cd ../..

# Run tests and generate coverage report
echo "Running tests and generating coverage report..."
cd build/debug
./tests/PersonTest  # Run the Google Test binary directly
gcovr -r ../.. --html --html-details -o coverage.html
echo "Coverage report generated: build/debug/coverage.html"
cd ../..

# Build Release version
echo "Building Release version..."
cd build/release
cmake -DCMAKE_BUILD_TYPE=Release ../..
make
cd ../..

echo "Build completed successfully for both Debug and Release versions."