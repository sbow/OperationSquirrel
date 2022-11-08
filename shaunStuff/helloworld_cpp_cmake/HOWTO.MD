## Basic Tutorial on Creating a Docker Container

- Create an account on dockerhub (free), dont have too long a name, ull b using it in commands ie: shaunbdockerhub
- Ensure u have Ubuntu on WSL2
- Install docker on nano, install docker on wsl2, install Docker Desktop on windows

## Log into your docker hub account from WSL2 - on x86 host
- me@myComp: ~/$ docker login

### Get this repo - all this on x86 host
- git clone https://github.com/sbow/OperationSquirrel
- cd OperationSquirrel/shaunStuff/helloworld_cpp_cmake


### Build docker container - all this on x86 host
- build the docker container:         ```      docker build -t hellocppcmake:v1```
- test the docker container:          ```      docker run -it hellocppcmake:v1```
- observe the docker container data:  ```      docker images```

## Push docker container to cloud - all this on x86 host
- tag the new container for push to dockerHub: ```docker tag 4c0845b9f9b6 shaunbdockerhub/hellocppcmake:v1```
  - where: 4c0845b9f9b6 is the IMAGE ID from "docker images"
  - where: shaunbdockerhub is your docker up login
  - where: hellocppcmake:v1 is whatever u want the remote repo to be called
- push the container to dockerhub:            ```docker push shaunbdockerhub/hellocppcmake:v1```

### Get this repo and run - on nano
- ```me@myNano: ~/$ sudo docker pull shaunbdockerhub/hellocppcmake:v1```
- ```me@myNano: ~/$ sudo docker run -it shaunbdockerhub/hellocppcmake:v1```



# Resources for getting unstuck

- Base container from nVidia: [website](https://catalog.ngc.nvidia.com/orgs/nvidia/containers/l4t-base?fbclid=IwAR1rJIqQXpaxa2ALgR_0bP07PYeaTo_A_E7_9tW1ygnpqrIYCYaEinoCj1c). Dockerfile base container FROM resource: nvcr.io/nvidia/l4t-base:r32.7.1

- Docker Desktop WSL backend on windows: [website](https://docs.docker.com/desktop/windows/wsl/?fbclid=IwAR0XdHzFS4EzO9O1qG2s_te46MHLsCdnBWc5063oZ2Q8Hvgx77eVYwBPkn8)

- Good example for getting Docker Compose / docker running / verified on jetson: [website] (https://collabnix.com/running-docker-compose-on-nvidia-jetson-nano-in-5-minutes/?fbclid=IwAR2-gQTrZbgrjfC3ijQWeiMHW2C64Nsc3qzUo1VJR1vio6ayBVzZvoDj-d4)

- Good example for getting cross compiling docker image from wsl / x86 to Nano. However, note their example requires a specific camera. It is better to use this example instead, basically a "hello world". [website] (https://collabnix.com/running-docker-compose-on-nvidia-jetson-nano-in-5-minutes/?fbclid=IwAR2-gQTrZbgrjfC3ijQWeiMHW2C64Nsc3qzUo1VJR1vio6ayBVzZvoDj-d4)
