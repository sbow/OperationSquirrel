# Specify the parent image from which we build
FROM dustynv/jetson-inference:r32.7.1

# Keep the container running
ENTRYPOINT ["tail", "-f", "/dev/null"]

RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null \
    && echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ bionic main' | tee /etc/apt/sources.list.d/kitware.list >/dev/null

# setup dependancies needed inside the container (not apt-get update)
RUN set -ex;                                                \
    apt-get update;                                

# Set the working directory inside the container
WORKDIR /app

# Copy files from your host to the working directory in the container
COPY ./container_src container

# Build the application with cmake inside the container
RUN set -ex;                                                \
    cd /app/container/build;                                \
    cmake ..;                                               \
    make;

# Run the application
#CMD ["/app/container/build/my-recognition"]
