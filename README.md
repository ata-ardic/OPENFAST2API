OpenFAST2API
OpenFAST2API is a C++ API wrapper for OpenFAST, designed to allow easy interaction with the OpenFAST wind turbine simulation tool. This project demonstrates how to integrate OpenFAST into a C++ program and interact with its functionalities.

Table of Contents
Prerequisites
Installation Instructions
Building the Project
Running the Example
Docker Support
Troubleshooting
Prerequisites
Before building and running the project, make sure the following tools and libraries are installed:

Operating System: Linux, macOS, or Windows (with WSL)
Dependencies:
CMake: Version 3.16 or higher
C++ Compiler: GCC or Clang
OpenFAST: The OpenFAST wind turbine simulation tool
HDF5: Library for data storage (optional, depending on the project)
To install the necessary dependencies on Ubuntu:

bash
Copy code
sudo apt-get update
sudo apt-get install -y build-essential cmake libhdf5-dev
Installation Instructions
Clone the repository:

bash
Copy code
git clone https://github.com/ata-ardic/OPENFAST2API.git
cd OPENFAST2API
Install OpenFAST (if not already installed): Follow the instructions in the OpenFAST GitHub repository to download and install OpenFAST.

Once installed, make sure OpenFAST is in your system's PATH so it can be found by the project.

Building the Project
After cloning the repository, you need to build the project using CMake. Follow the steps below:

Create a build directory:

bash
Copy code
mkdir build
cd build
Configure the project using CMake:

bash
Copy code
cmake ..
Build the project:

bash
Copy code
make -j8
This will build the project using 8 threads to speed up the compilation. You can change the number based on your system’s capabilities.
Running the Example
Once the build is complete, you can run the example to test that the integration with OpenFAST works:

Run the test_openfast executable:

bash
Copy code
./test_openfast
You should see output like:

bash
Copy code
Creating OpenFAST instance...
Initializing OpenFAST...
Initialization complete!
Docker Support
To ensure the project works in an isolated environment, you can use Docker to run the project in a container with all dependencies pre-configured.

Docker Setup
Build the Docker image:

bash
Copy code
docker build -t openfast2api .
Run the Docker container:

bash
Copy code
docker run openfast2api
This will execute the test_openfast program inside the Docker container.

Dockerfile (for reference)
dockerfile
Copy code
FROM ubuntu:20.04

# Install dependencies
RUN apt-get update && \
    apt-get install -y build-essential cmake git libhdf5-dev

# Clone OpenFAST and other dependencies
RUN git clone https://github.com/OpenFAST/openfast.git

# Set working directory
WORKDIR /OpenFAST2API

# Copy project files into container
COPY . /OpenFAST2API

# Build the project
RUN mkdir build && cd build && cmake .. && make -j8

# Default command to run your app
CMD ["./build/test_openfast"]
Troubleshooting
1. Build Failures
Make sure all dependencies are installed. If you're using a Linux system, you can install the necessary packages with:

bash
Copy code
sudo apt-get install build-essential cmake libhdf5-dev
Check that OpenFAST is correctly installed and accessible in your system's PATH.

2. Docker Issues
Ensure Docker is installed and running on your machine. Follow the installation guide for Docker here.
