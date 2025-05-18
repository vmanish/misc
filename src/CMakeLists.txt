# Add source files
set(SOURCES
    main.cpp
    Person.cpp
    MergeSortStrategy.cpp  # Add this line
    InsertionSortStrategy.cpp  # Add this line if not already present
)

# Add header files
set(HEADERS
    Person.hpp
)

# Add the library for shared code
add_library(misc_lib
    Person.cpp
    MergeSortStrategy.cpp  # Add this line
    InsertionSortStrategy.cpp  # Add this line if not already present
)

# Add the include directory for the library
target_include_directories(misc_lib PUBLIC ../include)

# Add the executable for the main application
add_executable(misc main.cpp)

# Link the library to the executable
target_link_libraries(misc PRIVATE misc_lib)

# Include directories
target_include_directories(misc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})