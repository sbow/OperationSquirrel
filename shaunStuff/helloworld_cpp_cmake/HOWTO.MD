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
