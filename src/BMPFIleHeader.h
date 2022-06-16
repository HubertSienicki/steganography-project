//
// Created by kneiv on 6/16/2022.
//

#ifndef STEGANOGRAPHY_PROJECT_BMPFILEHEADER_H
#define STEGANOGRAPHY_PROJECT_BMPFILEHEADER_H
#include <cstdint>

/**
 * FileHeader structure for .bmp files
 */
struct BMPFileHeader {
    [[maybe_unused]] std::uint16_t signature{0x4D42};//File signature ALWAYS: MB or 0x4D(B)42(M)
    std::uint32_t fileSize{0};                       //Size of a file in bits;
    std::uint32_t data_offset{0};                    //Offset from the start of a file to the bitmap data
};
#endif//STEGANOGRAPHY_PROJECT_BMPFILEHEADER_H
