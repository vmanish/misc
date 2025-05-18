# Use a lightweight Alpine Linux image
FROM alpine:3.18

# Set environment variables to avoid interactive prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Install required packages
RUN apk add --no-cache \
    build-base \
    cmake \
    git \
    linux-headers

# Download and build Google Test
RUN git clone https://github.com/google/googletest.git /usr/src/gtest && \
    cd /usr/src/gtest && \
    cmake . && \
    make && \
    mkdir -p /usr/include/gtest /usr/include/gmock && \
    cp -r googletest/include/gtest/* /usr/include/gtest/ && \
    cp -r googlemock/include/gmock/* /usr/include/gmock/ && \
    cp lib/*.a /usr/lib

# Set the working directory inside the container
WORKDIR /usr/src/app

# Copy the project files into the container
COPY . .

# Create build directories and build Debug and Release versions
RUN mkdir -p build/debug build/release && \
    cd build/debug && \
    cmake -DCMAKE_BUILD_TYPE=Debug ../.. && \
    make && \
    cd ../release && \
    cmake -DCMAKE_BUILD_TYPE=Release ../.. && \
    make

# Default command to list the built binaries
CMD ["sh", "-c", "ls -l ./build/debug/src/misc ./build/release/src/misc ./build/debug/tests/PersonTest ./build/release/tests/PersonTest"]