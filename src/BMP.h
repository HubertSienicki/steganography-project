//
// Created by kneiv on 5/16/2022.
//

#ifndef STEGANOGRAPHY_PROJECT_BMP_H
#include <bitset>
#include <cstdint>
#include <fstream>
#include <vector>
#define STEGANOGRAPHY_PROJECT_BMP_H

struct BMPFileHeader {
    std::uint16_t signature{0x4D42};//File signature ALWAYS: MB or 0x4D(B)42(M)
    std::uint32_t fileSize{0};      //Size of a file in bits;
    std::uint32_t data_offset{0};   //Offset from the start of a file to the bitmap data
};

struct BMPInfoHeader {
    std::uint32_t header_size{0};   //Size of info header
    std::int32_t width{0};          //Width of a bitmap
    std::int32_t height{0};         //Height of a bitmap
    std::uint32_t planes{0};        //UNUSED planes of a bitmap
    std::uint16_t bits_per_pixel{0};//Stores color palette informaiton ->
    /*   1 - monochrome
     *   4 - max of 16 colors
     *   8 - 256 colors
     *   16 - 2^16 colors
     *   24 - 2^24 colors
     *   etc..
     */
    std::uint32_t compression{4};//Stores compression data
    std::uint32_t image_size{4}; //"compressed" size of an image
};

struct BMP {
    BMPFileHeader bmp_file_header;
    BMPInfoHeader bmp_info_header;

    const char *filename;
    int dataSize;
    unsigned char *dataCopy;
    int bitsToEncode;


    BMP(const char *filename, std::string message);//Encoding constructor
    BMP(const char *filename, int seed);           //Decoding constructor;
    BMP(const char *filename);                     //Default constructor for reading.


    void readBMP(const char *filename);
    void readBMPFileHeader(std::ifstream &input);
    void readBMPInfoHeader(std::ifstream &input);
    void encodeMessage(std::ifstream &input, std::string message);
    void decodeMessage(std::ifstream &input, int seed);
    void writeBitmap();
    int generateSeed();
    void printBitMapInformation();

private:
    void copyData(std::ifstream &input);
};


#endif//STEGANOGRAPHY_PROJECT_BMP_H
