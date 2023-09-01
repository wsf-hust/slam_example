cmake_minimum_required(VERSION 3.26)
project(slam_example)

set(CMAKE_CXX_STANDARD 11)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
#include_directories("/usr/include/eigen3")
#add_executable(slam_example main.cpp)

add_executable(slam_example use_geometry.cpp)
