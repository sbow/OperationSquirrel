# Specify the parent image from which we build
FROM dustynv/jetson-inference:r32.7.1

# Keep the container running
#ENTRYPOINT ["tail", "-f", "/dev/null"]

RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null \
    && echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ bionic main' | tee /etc/apt/sources.list.d/kitware.list >/dev/null

# setup dependancies needed inside the container (not apt-get update)
RUN set -ex;                                                \
    apt-get update;                                         \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    xserver-xorg-video-dummy \
    x11-xserver-utils \
    x11-apps \
    g++ \
    cmake \
    make \
    mesa-utils;

# Set the working directory inside the container
WORKDIR /app

# Copy files from your host to the working directory in the container
COPY ./container_src container

# Build the application with cmake inside the container
RUN set -ex;  \                                             
    mkdir -p /app/container/build;\
    cd /app/container/build;      \                         
    cmake ..;                     \                          
    make;

# Set environment variable for X11 forwarding
ENV DISPLAY=:0

# Run the application with X11 forwarding enabled
CMD ["/bin/bash", "-c", "service nvargus-daemon start && while :; do /app/container/build/my-recognition; done"]

