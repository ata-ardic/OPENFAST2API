# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Set project name and the C++ standard
project(runOPENFAST)
set(CMAKE_CXX_STANDARD 17)  # Adjust to C++17 or other versions if needed

# Find MPI
find_package(MPI REQUIRED)

# Include OpenFAST, HDF5, and MPI headers
include_directories(
    /home/inflows/Documents/OpenFAST/install/include/
    ${HDF5_INCLUDE_DIRS}   # Add HDF5 include directories
    ${MPI_INCLUDE_PATH}    # Add MPI include directories
)

# Link directories for OpenFAST, HDF5, and MPI
link_directories(
    /home/inflows/Documents/OpenFAST/install/lib/
)

# Find and link HDF5
find_package(HDF5 REQUIRED)
include_directories(${HDF5_INCLUDE_DIRS})

# Define the executable
add_executable(test_openfast test_openfast.cpp)

# Link OpenFAST, HDF5, and MPI libraries to the executable
target_link_libraries(test_openfast openfastcpplib ${HDF5_LIBRARIES} ${MPI_LIBRARIES})
