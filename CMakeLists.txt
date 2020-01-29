cmake_minimum_required(VERSION 3.14)
project(strsv)
enable_testing()

# Externally provided libraries
add_subdirectory(dependencies)

## Project-wide setup
# note: google benchmark has a CMake bug, so
# these need to be moved after dependencies.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# Our sources
add_subdirectory(src)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    add_subdirectory(tests)
endif ()