CC = g++
CFLAGS = -I../../libraries/mavlink/generated/include/mavlink/v2.0/common

# list of object files
OBJ = mavlink2_example.o

# default target
all: mavlink2_example

# compile source code into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# link object files into executable
mavlink2_example: $(OBJ)
	$(CC) $(OBJ) -o $@

# clean up object and executable files
clean:
	rm -f $(OBJ) mavlink2_example

