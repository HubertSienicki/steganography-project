//
// Created by kneiv on 6/15/2022.
//

#ifndef STEGANOGRAPHY_PROJECT_PPM_H
#include <iostream>
#define STEGANOGRAPHY_PROJECT_PPM_H

/*
 * 16 byte header
 */
struct PPMHeader {
    std::uint16_t signature;// should be 5036
    std::int8_t width[4];
    std::int8_t height[4];
    std::int8_t colorMax[3];
    int data_offset;
};

struct PPM {
    PPMHeader header{};

    const char* filename;
    int dataSize{};
    int fileSize{};
    unsigned char* dataCopy{};

    explicit PPM(const char* filename);
    PPM(const char* filename, std::string message);
    PPM(const char* filename, int seed);

    void readPPM(std::ifstream& input);
    void writePPM() const;
    void printPPMInfo() const;

    void encode(std::ifstream& input, std::string message) const;



    void copyData(std::ifstream& input);
    void printImageSize() const;
    void bitSwitch(std::string message, int messageLength) const;
};


#endif//STEGANOGRAPHY_PROJECT_PPM_H
