//
// Created by kneiv on 6/16/2022.
//

#ifndef STEGANOGRAPHY_PROJECT_PPMHEADER_H
#define STEGANOGRAPHY_PROJECT_PPMHEADER_H


#include <cstdint>
struct PPMHeader {
    std::uint16_t signature;// should be 5036 or P3
    std::int8_t width[4];
    std::int8_t height[4];
    std::int8_t colorMax[3];
    int data_offset;
};


#endif//STEGANOGRAPHY_PROJECT_PPMHEADER_H
