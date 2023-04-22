# cmake_minimum_required(VERSION 3.10)
# project(simple_camera)
# 
# # Set C++11 standard
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)
# 
# add_executable(simple_camera main.cpp)
# 
# -----------------

cmake_minimum_required(VERSION 3.10)

project(simple_camera)

# Set C++11 standard
set(CMAKE_CXX_STANDARD 11)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Add include directories for OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Add link directories for OpenCV
link_directories(${OpenCV_LIB_DIR})

# Add executable target
add_executable(simple_camera simple_camera.cpp)

# Link against OpenCV libraries
target_link_libraries(simple_camera ${OpenCV_LIBS})
