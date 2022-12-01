# About
This folder contains scratch containers that are not yet ready for the main development of Operation Squirrel code.  It is essentially a sandbox where different containers can be created and tested.  Each subfolder shall contain the necessary depencies to build a container.

Before building one of these containers, make sure you are in the qemu emulation environment which will emulate the jetson nano's ARM architecture.  Instructions to do so can be found at https://www.stereolabs.com/docs/docker/building-arm-container-on-x86/, but will also be listed below.

# Install qemu packages (only needs to be done once)
sudo apt-get install qemu binfmt-support qemu-user-static # Install the qemu packages

# Enter emulation environment (needs to be done before building/running containers intended for jetson nano)
docker run --rm --privileged multiarch/qemu-user-static --reset -p yes # This step will execute the registering scripts

# Checking that the emulation environment is running (not necessary but good to check before executing docker build /run commands on the x86 host)
docker run --rm -t arm64v8/ubuntu uname -m # Testing the emulation environment

aarch64 # this is the response you should get