//
// Created by kneiv on 5/17/2022.
//

#ifndef STEGANOGRAPHY_PROJECT_PNG_H
#include <iostream>
#define STEGANOGRAPHY_PROJECT_PNG_H


//InfoHeader
struct IHDRChunk {
    std::uint16_t signature;//PNG
    std::uint16_t width;
    std::uint16_t height;
    std::uint8_t bit_depth;
    std::uint8_t color_type;// must be 2!!!!!!
    std::uint16_t final;
};

//Defined chunk of data;
struct IDATChunk {
    std::uint16_t header;
};

struct PNGFileHeader {
    std::uint32_t magicNumber;
    IHDRChunk InfoHeader;
};

struct PNG {
    const char* filename;
    PNGFileHeader file_header;
    IDATChunk* data;

    PNG(const char* filename);                     //Default read constructor
    PNG(const char* filename, std::string message);//Message to encode
    PNG(const char* filename, int seed);           //Default to decode


    void readPNG(std::ifstream& input);
    void encode(std::ifstream& input, std::string message);
    void decode(std::ifstream& input, int seed);
    void writePNG();
    void printPNGInfo();
    int generateSeed();
};


#endif//STEGANOGRAPHY_PROJECT_PNG_H
