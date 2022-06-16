cmake_minimum_required(VERSION 3.22)
project(steganography_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(steganography_project main.cpp src/BMP.cpp src/BMP.h src/PPM.cpp src/PPM.h src/PPMHeader.h src/BMPFIleHeader.h src/BMPInfoHeader.h)
