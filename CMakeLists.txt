cmake_minimum_required(VERSION 3.12.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(nns)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

find_package (Eigen3 3.3.7 REQUIRED NO_MODULE)

include_directories(.)

file(GLOB SOURCES "bin/*.cpp")
file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test/data/*.cpp)

add_executable(tests ${TEST_SOURCES})
add_executable(train ${SOURCES})
