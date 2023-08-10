CC = g++
CFLAGS = -I./inc/mavlink/v2.0/common -I.

# get list of all .cpp files in the source directory
SRCS := $(wildcard *.cpp)

# generate list of object files
OBJ := $(SRCS:.cpp=.o)

# Define the configuration flag
# Use UART functionality on Jetson Nano
CFLAGS += -DUSE_UART
# Use TCP functionality
# CFLAGS += -DUSE_TCP

# OpenCV flags
OPENCV_CFLAGS = $(shell pkg-config --cflags opencv4)  # Note the change from opencv to opencv4
OPENCV_LIBS = $(shell pkg-config --libs opencv4)      # Note the change from opencv to opencv4

# GStreamer flags
GST_CFLAGS = $(shell pkg-config --cflags gstreamer-1.0 gstreamer-video-1.0)
GST_LIBS = $(shell pkg-config --libs gstreamer-1.0 gstreamer-video-1.0)

# Combine all flags
CFLAGS += $(OPENCV_CFLAGS) $(GST_CFLAGS)
LIBS = -lrt $(OPENCV_LIBS) $(GST_LIBS)

# default target
all: main

# compile source code into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# link object files into executable
main: $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

# clean up object and executable files
clean:
	rm -f $(OBJ) main

