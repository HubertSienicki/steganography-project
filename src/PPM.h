//
// Created by kneiv on 6/15/2022.
//

#ifndef STEGANOGRAPHY_PROJECT_PPM_H
#include "PPMHeader.h"
#include <iostream>
#define STEGANOGRAPHY_PROJECT_PPM_H

class PPM {
private:
    PPMHeader header{};

    const char* filename;
    int dataSize{};
    int fileSize{};
    unsigned char* dataCopy{};
    int bitsToEncode{};

    void readPPM(std::ifstream& input);
    void writePPM() const;
    void copyData(std::ifstream& input);
    void printImageSize() const;
    void bitSwitch(std::string message, int messageLength) const;
    [[nodiscard]] int generateSeed() const;

public:
    explicit PPM(const char* filename);            // read
    PPM(const char* filename, const std::string& message);//encode
    PPM(const char* filename, int seed);           //decode
    virtual ~PPM();

    void printPPMInfo() const;
    void encode(std::ifstream& input, const std::string& message);
    void decode(std::ifstream& input, int seed) const;
    void check(const std::string& message) const;
};


#endif//STEGANOGRAPHY_PROJECT_PPM_H
