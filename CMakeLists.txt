cmake_minimum_required(VERSION 3.8)
project(FDPv1)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES library.cpp library.h FDPMessage.cpp FDPMessage.h)
add_library(FDPv1 ${SOURCE_FILES})
add_executable(FDPv1e main.cpp)