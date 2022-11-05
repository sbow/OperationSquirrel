# Specify the parent image from which we build
FROM nvcr.io/nvidia/l4t-base:r32.7.1

# Set the working directory
WORKDIR /home/shaun/my_docker/docker_bld

# Copy files from your host to your current working directory
COPY container_src hello_cpp_cmake_cntnr

# Build the application with cmake
RUN cd /home/shaun/my_docker/docker_bld && \
    cmake -DCMAKE_LIBRARY_PATH=/usr/local/cuda/lib64/stubs \
      -DCMAKE_CXX_FLAGS="-Wl,--allow-shlib-undefined" .. && \
    make

# Run the application
CMD ["/home/shaun/my_docker/docker_bld/hello_cpp_cmake_cntnr/build/helloworld_cmake_cpp"]
