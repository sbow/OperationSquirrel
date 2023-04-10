# Use the official C++ image as the base image
FROM gcc:latest

# Set the working directory
WORKDIR /app

# Install necessary packages
RUN apt-get update && \
    apt-get install -y cmake libopencv-dev

# Copy the CMakeLists.txt and source files into the container
COPY . .

# Create a build directory and run CMake
RUN mkdir build && \
    cd build && \
    cmake .. && \
    make

# Set the command to run your program when the container starts
CMD ["./build/helloworld2_cpp_cmake"]