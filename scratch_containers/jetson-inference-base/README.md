# Here are the build and run commands
sudo docker build . -t cameroncrose72/jetson-nano-test:base_image_dusty-nv

sudo docker run --rm --gpus all -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix --device=/dev/video0 --net=host cameroncrose72/jetson-nano-test:base_image_dusty-nv /app/container/build/my-recognition
