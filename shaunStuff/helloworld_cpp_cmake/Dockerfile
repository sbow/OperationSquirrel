# Use the official C++ image as the base image
FROM gcc:latest

# Set the working directory
WORKDIR /app

# Copy the CMakeLists.txt and source files into the container
COPY . .

# Install CMake
RUN apt-get update && \
    apt-get install -y cmake

# Create a build directory and run CMake
RUN mkdir build && \
    cd build && \
    cmake .. && \
    make

# Set the command to run your program when the container starts
CMD ["./build/helloworld_cpp_cmake"]
