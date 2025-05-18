# misc

## Overview
This project demonstrates a C++ application with unit tests using Google Test. Below are the instructions to build and run the project locally on Ubuntu and inside a Docker container.

---

## Local Ubuntu Environment

### Prerequisites
Ensure the following packages are installed:
- `build-essential`
- `cmake`
- `git`
- `libgtest-dev`

### Steps to Build 

1. **Run the Installation Script**:
   Use the provided `install_local_ubuntu.sh` script to set up the environment and build the project:
   ```bash
   ./install_local_ubuntu.sh
   ```

2. **Build the Application & unit tests**:
   After building, run the main application:
   ```bash
   ./build.sh
   ```

---

## Docker Environment

### Prerequisites
Ensure Docker or Podman is installed on your system.

### Steps to Build 

1. **Build the Docker Image**:  you can use docker as well.
   Build the Docker image using the provided `Dockerfile`:
   ```bash
   podman build -t misc .
   ```

2. **Run Interactively (Optional)**:
   If you want to debug or manually run commands inside the container:
   ```bash
   podman run --rm -it misc sh
   ```
---

## Steps to run the application & tests 

1. **Run the Application**:
   After building, run the main application:
   ```bash
   ./build/release/src/misc
   ```

2. **Run the Tests**:
   Execute the test suite:
   ```bash
   ./build/release/tests/PersonTest
---

## Notes
- The `install_local_ubuntu.sh` script is designed for Ubuntu-based systems and automates the setup process.
- The Docker environment provides an isolated setup, ensuring consistent builds and runs across different systems.