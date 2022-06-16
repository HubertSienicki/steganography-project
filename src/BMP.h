//
// Created by kneiv on 5/16/2022.
//
#ifndef STEGANOGRAPHY_PROJECT_BMP_H
#include "BMPFIleHeader.h"
#include "BMPInfoHeader.h"
#include <bitset>
#include <fstream>
#include <vector>
#define STEGANOGRAPHY_PROJECT_BMP_H

class BMP {
private:
    BMPFileHeader bmp_file_header;
    BMPInfoHeader bmp_info_header;

    const char* filename;
    int dataSize{};
    unsigned char* dataCopy{};
    int bitsToEncode{};

    void copyData(std::ifstream& input);
    void writeBitmap() const;
    void encodeMessage(std::ifstream& input, std::string message);
    void decodeMessage(std::ifstream& input, int seed) const;

    void readBMP(const char* path);
    void readBMPFileHeader(std::ifstream& input);
    void readBMPInfoHeader(std::ifstream& input);

public:
    BMP(const char* filename, std::string message);//Encoding constructor
    BMP(const char* filename, int seed);           //Decoding constructor;
    explicit BMP(const char* filename);            //Default constructor for reading.

    [[nodiscard]] int generateSeed() const;
    void printBitMapInformation() const;
    void check(const std::string& message) const;
};


#endif//STEGANOGRAPHY_PROJECT_BMP_H
