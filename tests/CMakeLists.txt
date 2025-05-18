# Enable testing
enable_testing()

# Manually specify GTest paths (Alpine-specific)
set(GTEST_INCLUDE_DIR /usr/include)
set(GTEST_LIBRARY /usr/lib/libgtest.a)
set(GTEST_MAIN_LIBRARY /usr/lib/libgtest_main.a)

# Add the test executable
add_executable(PersonTest PersonTest.cpp)

# Add the include directory for the test executable
target_include_directories(PersonTest PRIVATE ${GTEST_INCLUDE_DIR} ../include)

# Link the test executable with Google Test and the shared library
target_link_libraries(PersonTest PRIVATE ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} pthread misc_lib)

# Add the test to CTest
add_test(NAME PersonTest COMMAND PersonTest)