CC = g++
CFLAGS = -I./inc/mavlink/v2.0/common -I.

# get list of all .cpp files in the source directory
SRCS := $(wildcard *.cpp)

# generate list of object files
OBJ := $(SRCS:.cpp=.o)

# Define the configuration flag
# Use UART functionality on Jetson Nano
# CFLAGS += -DUSE_UART
# Use TCP functionality
CFLAGS += -DUSE_TCP

# default target
all: main

# compile source code into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# link object files into executable
main: $(OBJ)
	$(CC) $(OBJ) -o $@ -lrt

# clean up object and executable files
clean:
	rm -f $(OBJ) main
