# Specify the parent image from which we build
FROM cameroncrose72/jetson-nano-test:base_image

# Keep the container running
#ENTRYPOINT ["tail", "-f", "/dev/null"]

# setup dependancies needed inside the container
RUN set -ex;                                                  \
    apt-get update;                                           \
jetson-nano-base copy    apt-get install -y g++ curl cmake libzmq3-dev;         

# Install ffmpeg
#RUN apt install ffmpeg;                                       \
#    ffmpeg -version;                                          \
#    y;

# Set the working directory inside the container
WORKDIR /app

# Copy files from your host to the working directory in the container
COPY ./container_src container

# Build the application with cmake inside the container
RUN set -ex;                                                \
    cd /app/container/build;                                      \
    cmake ..;                                               \
    make;

# Run the application
CMD ["/app/container/build/hello_world"]
