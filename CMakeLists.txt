cmake_minimum_required(VERSION 3.22)
project(steganography_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(steganography_project main.cpp src/BMP.cpp src/BMP.h src/PNG.cpp src/PNG.h src/PNGFIleHeader.cpp src/PNGFIleHeader.h)
