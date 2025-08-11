# Sets Minimum Allowed CMake Version 
cmake_minimum_required(VERSION 2.8...3.5)

# Project Name 
project(tutorial LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

# Find MPI
find_package(MPI REQUIRED)
if (MPI_COMPILER_FLAGS)
  add_compile_options(${MPI_COMPILER_FLAGS})
endif()
include_directories(${MPI_INCLUDE_PATH})
set(EXTERNAL_LIBS ${MPI_LIBRARIES})
set(MPICXX "mpicxx" CACHE STRING "MPICXX command")
set(MPIRUN "mpirun" CACHE STRING "MPIRUN command")

set(SOURCE_NAME "src")

# Adds Compile Warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wshadow")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Wshadow")

# Will Include Files in Current Directory
set(tutorial_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(src_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_NAME})

include_directories(${src_DIR})
include_directories(${hw_DIR})

# Add SRC Directory with Professor's Starter Code
add_subdirectory(${SOURCE_NAME})

# Create Library
# TODO : Include your new file here!
add_library(tutorial STATIC
    ${src_SOURCES}
    main.cpp
    )

# Add Directory with Tutorial Unit Tests
enable_testing()
add_subdirectory(${SOURCE_NAME}/tests)

add_subdirectory(examples)



