# Specify the parent image from which we build
FROM nvcr.io/nvidia/l4t-base:r32.7.1

# setup dependancies needed inside the container
RUN set -ex;                                                  \
    apt-get update;                                           \
    apt-get install -y g++ curl cmake libzmq3-dev;            

# Set the working directory inside the container
WORKDIR /app

# Copy files from your host to the working direcoty in the container
COPY ./container_src hello_cpp_cmake_cntnr


# Build the application with cmake inside the container
RUN set -ex;                                                \
    cd /app/hello_cpp_cmake_cntnr/build;                    \
    cmake ..;                                               \
    make;

# Run the application
CMD ["/app/hello_cpp_cmake_cntnr/build/helloworld_cmake_cpp"]
