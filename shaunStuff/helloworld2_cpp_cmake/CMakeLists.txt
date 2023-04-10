cmake_minimum_required(VERSION 3.10)
project(helloworld2_cpp_cmake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)

add_executable(helloworld2_cpp_cmake main.cpp)

target_link_libraries(helloworld2_cpp_cmake ${OpenCV_LIBS})