cmake_minimum_required(VERSION 3.0)

# Project Name - can be whatever
project(cmake-demo)

# Specify desired name of executable
set(MYEXEC helloworld_cmake_cpp)

# Specify location of src files, './src' in this case
set(MYSRC src)

# Specify location of includes, './includes' in this case
set(MYINCLUDES includes)

# Set the C++14 standard
set(CMAKE_CXX_STANDARD 14)

# I../includes
include_directories(${MYSRC} ${MYINCLUDES})


# Put all .cpp files inside src into SOURCES variable
file(GLOB SOURCES
	${MYSRC}/*.cpp
)

#set(SOURCE src/main.cpp)

# compiles the files defined by SOURCES to generate exec difened by EXEC
add_executable(${MYEXEC} ${SOURCES})
