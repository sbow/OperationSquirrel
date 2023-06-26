CC = g++
CFLAGS = -I../../../libraries/mavlink/generated/include/mavlink/v2.0/common

# list of object files
OBJ = sitl_example_TCP.o

# default target
all: sitl_example_TCP

# compile source code into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# link object files into executable
sitl_example_TCP: $(OBJ)
	$(CC) $(OBJ) -o $@

# clean up object and executable files
clean:
	rm -f $(OBJ) sitl_example_TCP

