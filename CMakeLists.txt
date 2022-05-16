cmake_minimum_required(VERSION 3.22)
project(steganography_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(steganography_project main.cpp src/BMP.cpp src/BMP.h src/BMPInfoHeader.cpp src/BMPInfoHeader.h src/BMPColorHeader.cpp src/BMPColorHeader.h src/BMPFileHeader.cpp src/BMPFileHeader.h)
