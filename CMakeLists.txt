# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Set project name and the C++ standard (adjust as needed)
project(runOPENFAST)
set(CMAKE_CXX_STANDARD 17)  # Adjust to C++17 or other versions if needed

# Include OpenFAST headers
include_directories(
    /home/ata/Documents/OpenFAST/build/your_install_path/include/
    ${HDF5_INCLUDE_DIRS}  # Add HDF5 include directories as well
)

# Link directories for OpenFAST and HDF5
link_directories(
    /home/ata/Documents/OpenFAST/build/your_install_path/lib/
)

# Find and link HDF5
find_package(HDF5 REQUIRED)
include_directories(${HDF5_INCLUDE_DIRS})

# Define the executable
add_executable(test_openfast test_openfast.cpp)

# Link OpenFAST and HDF5 libraries to the executable
target_link_libraries(test_openfast openfastcpplib ${HDF5_LIBRARIES})
