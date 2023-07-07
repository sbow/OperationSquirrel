CC = g++
CFLAGS = -I./inc/mavlink/v2.0/common

# get list of all .cpp files in the source directory
SRCS := $(wildcard *.cpp)

# generate list of object files
OBJ := $(SRCS:.cpp=.o)

# default target
all: main

# compile source code into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# link object files into executable
main: $(OBJ)
	$(CC) $(OBJ) -o $@

# clean up object and executable files
clean:
	rm -f $(OBJ) main

