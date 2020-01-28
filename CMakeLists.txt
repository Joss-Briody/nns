cmake_minimum_required(VERSION 3.12.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(nns)

find_package (Eigen3 3.3.7 REQUIRED NO_MODULE)

include_directories(.)
file(GLOB SOURCES "*.cpp")

add_executable(train ${SOURCES})
