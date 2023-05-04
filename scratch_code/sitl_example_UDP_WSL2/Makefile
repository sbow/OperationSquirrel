CC = g++
CFLAGS = -I../../../libraries/mavlink/generated/include/mavlink/v2.0/common

# list of object files
OBJ = sitl_example_UDP.o

# default target
all: sitl_example_UDP

# compile source code into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# link object files into executable
mavlink2_example: $(OBJ)
	$(CC) $(OBJ) -o $@

# clean up object and executable files
clean:
	rm -f $(OBJ) sitl_example_UDP

