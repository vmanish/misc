cmake_minimum_required(VERSION 3.10)

# Project name
project(misc)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable coverage flags for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Enabling coverage flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Add the src directory
add_subdirectory(src)

# Add the tests directory
add_subdirectory(tests)