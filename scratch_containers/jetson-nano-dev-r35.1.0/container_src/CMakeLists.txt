cmake_minimum_required(VERSION 3.0)

# Project Name - can be whatever
project(cmake-demo)

# Specify desired name of executable
set(MYEXEC hello_world)

# Specify location of src files, './src' in this case
set(MYSRC src)

# Specify location of includes, './inc' in this case
set(MYINCLUDES inc)
set(OPENCV_PATH "/usr/local/include/opencv4/")

# Set the C++14 standard
set(CMAKE_CXX_STANDARD 14)

# I../includes
find_package(OpenCV REQUIRED)
include_directories(${MYSRC} ${MYINCLUDES})
include_directories(${OPENCV_PATH})

# Put all .cpp files inside src into SOURCES variable
file(GLOB SOURCES
	${MYSRC}/*.cpp
)

#set(SOURCE src/main.cpp)

# compiles the files defined by SOURCES to generate exec difened by EXEC
add_executable(${MYEXEC} ${SOURCES})

# Link your application with OpenCV libraries
target_link_libraries(${MYEXEC} PRIVATE ${OpenCV_LIBS})