# Force CMake version 3.1 or above
cmake_minimum_required (VERSION 3.1)

# This project has the name: parallel-programming
project (parallel-programming)

# Force use of C99 standard
set(CMAKE_C_FLAGS "-std=c99")

# Force Release build
set(CMAKE_BUILD_TYPE "Release")

# Set optimization for GCC gcc
if(CMAKE_COMPILER_IS_GNUCC)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -fopt-info-vec")
endif()

# Set optimization for GCC g++
if(CMAKE_COMPILER_IS_GNUCXX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -fopt-info-vec")
endif()

# Output message
message("Build all build targets of the parallel programming course")

# Enable/disable MPI
option(USE_MPI "Compile with MPI support" ON)

# Enable/disable OpenMP
option(USE_OpenMP "Compile with OpenMP support" ON)

# Enable/disable Threads
option(USE_Threads "Compile with Threads support" ON)

# Add subdirectories
add_subdirectory(introduction)
add_subdirectory(mpi)
add_subdirectory(openmp)
add_subdirectory(threads)
