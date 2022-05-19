//
// Created by kneiv on 5/16/2022.
//

#ifndef STEGANOGRAPHY_PROJECT_BMP_H
#include "BMPFileHeader.h"
#include "BMPInfoHeader.h"
#include <vector>
#define STEGANOGRAPHY_PROJECT_BMP_H





#include <cstdint>
#include <fstream>
#include <vector>


struct BMPFileHeader {
    std::uint16_t signature{0x4D42}; //File signature ALWAYS: MB or 0x4D(B)42(M)
    std::uint32_t fileSize{0}; //Size of a file in bytes;
    std::uint16_t unused1{0}; //unused
    std::uint16_t unused2{0}; //unused
    std::uint32_t data_offset{0}; //Offset from the start of a file to the bitmap data
};

struct BMPInfoHeader {
    std::uint32_t header_size{0}; //size of info header
    std::int32_t width{0}; //Width of a bitmap
    std::int32_t height{0}; // height of a bitmap
    std::uint32_t planes{0}; //UNUSED planes of a bitmap
    std::uint16_t bits_per_pixel{0}; //stores color palette informaiton ->
    /*   1 - monochrome
     *   4 - max of 16 colors
     *   8 - 256 colors
     *   16 - 2^16 colors
     *   24 - 2^24 colors
     *   etc..
     */
    std::uint32_t compression{4}; // stores compression data
    std::uint32_t image_size{4}; //"compressed" size of an image
};

struct BMP {
    BMPFileHeader bmp_file_header;
    BMPInfoHeader bmp_info_header;

    const char* filename;
    std::vector<unsigned char> data;


    BMP(const char* filename); //Invokes readBMP method;

    void readBMP(const char* filename);
    void readBMPFileHeader(std::ifstream& input);
    void readBMPInfoHeader(std::ifstream& input);
    void readBMPData(std::ifstream& input);

    unsigned char* writeBMP(int x, int y, int R, int G, int B);

    std::vector<unsigned int> getPixel(int x, int y);
    void copyBMP(char * newFileName);
    void displayPixels();

    int getWidth(){return this->bmp_info_header.width;};
    int getHeight(){return this->bmp_info_header.height;};

    std::uint16_t getSignature();
};


#endif //STEGANOGRAPHY_PROJECT_BMP_H
