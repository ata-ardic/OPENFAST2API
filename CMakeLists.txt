cmake_minimum_required(VERSION 3.16)

project(runOPENFAST)
set(CMAKE_CXX_STANDARD 17)

# Find required dependencies
find_package(MPI REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(HDF5 REQUIRED)

# Find libxml++ using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBXMLPP REQUIRED libxml++-2.6)

# Include directories
include_directories(
    /home/ata/Documents/OpenFAST/install/include/
    ${HDF5_INCLUDE_DIRS}
    ${MPI_INCLUDE_PATH}
    ${LIBXMLPP_INCLUDE_DIRS}
)

# Link directories
link_directories(
    /home/ata/Documents/OpenFAST/install/lib/
)

# Define source files
set(SOURCES
    test_openfast.cpp
)

# Define executable
add_executable(test_openfast ${SOURCES})

# Link necessary libraries
target_link_libraries(test_openfast
    openfastcpplib
    ${HDF5_LIBRARIES}
    yaml-cpp
    ${MPI_LIBRARIES}
    ${LIBXMLPP_LIBRARIES}
)
