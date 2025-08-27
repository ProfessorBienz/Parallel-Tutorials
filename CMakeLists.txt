# Sets Minimum Allowed CMake Version 
cmake_minimum_required(VERSION 3.12)

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


option(USE_C "C/C++ Version of Tutorail" ON)
option(USE_PY "Python Version of Tutorial" OFF)

if(USE_PY)
    find_package(Python COMPONENTS Interpreter Development REQUIRED)
    include_directories(${Python_INCLUDE_DIRS})   
    include_directories(SYSTEM ${MPI_INCLUDE_PATH})    
    execute_process(
    COMMAND ${Python_EXECUTABLE} -c "import sysconfig; print(sysconfig.get_paths()['purelib'])"
    OUTPUT_VARIABLE PY_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
    message(STATUS "Site Packages:" ${PY_SITE_PACKAGES})
    set(USE_C OFF)
    add_definitions(-DPY_MODULE_PATH=\"${CMAKE_SOURCE_DIR}/Python\")
    add_definitions(-DPY_SITE_PACKAGES=\"${PY_SITE_PACKAGES}\")
endif()

set(SOURCE_NAME "src")

# Adds Compile Warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wshadow")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Wshadow")

# Will Include Files in Current Directory
set(tutorial_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(src_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_NAME})

include_directories(${src_DIR})
include_directories(${tutorial_DIR})

# Add SRC Directory with Professor's Starter Code
add_subdirectory(${SOURCE_NAME})

# Create Library
# TODO : Include your new file here!
if (USE_C)
    add_library(tutorial STATIC
        ${src_SOURCES}
        C/main.cpp 
    )
    target_link_libraries(tutorial ${MPI_LIBRARIES}) 
elseif (USE_PY)
    message(STATUS "Creating python library")
    add_library(tutorial STATIC
        ${src_SOURCES}
        Python/main.cpp
    )
    target_link_libraries(tutorial ${MPI_LIBRARIES} Python::Python)
    message(STATUS "Add ${CMAKE_SOURCE_DIR}/Python to PYTHONPATH")
endif()

# Add Directory with Tutorial Unit Tests
enable_testing()
add_subdirectory(${SOURCE_NAME}/tests)

add_subdirectory(examples)



