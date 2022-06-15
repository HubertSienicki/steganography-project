//
// Created by kneiv on 6/15/2022.
//

#include "PPM.h"
#include <fstream>
#include <valarray>

PPM::PPM(const char* filename) {
    this->filename = filename;
    std::ifstream input(this->filename);

    if (!input) {
        std::cerr << "Could not open a file";
    } else {
        this->readPPM(input);
        this->printPPMInfo();
    }
}

PPM::PPM(const char* filename, std::string message) {
    this->filename = filename;
    std::ifstream input(this->filename);

    if (!input) {
        std::cerr << "Could not open a file";
    } else {
        this->readPPM(input);
        this->copyData(input);
    }
}

/**
 * Reads the bmp file;
 * @param input - input to a file
 */
void PPM::readPPM(std::ifstream& input) {
    int index = 0;//0->signature, 1-->width, 2-->height, 3-->Max color
    for (int i = 0; i < 16; ++i) {
        auto temp = (unsigned char) input.get();

        if (temp == '\n' || temp == ' ') {
            index++;
        } else {
            switch (index) {
                case 0:
                    this->header.signature = (this->header.signature << 8) | temp;
                    break;
                case 1:
                    this->header.width[i - 3] = (this->header.width[i - 3] << 8) | temp;
                    break;
                case 2:
                    this->header.height[i - 8] = (this->header.height[i - 8] << 8) | temp;
                    break;
                case 3:
                    this->header.colorMax[i - 13] = (this->header.colorMax[i - 11] << 8) | temp;
                    break;
                default:
                    std::cerr << "There was a problem with reading .ppm file. ";
                    break;
            }
        }
    }

    input.seekg(0, std::ios::end);
    this->fileSize = input.tellg();
    this->dataSize = fileSize * 8;
}

/**
 * Prints information about .ppm file;
 */
void PPM::printPPMInfo() const {
    std::cout << "Signature: 0x" << std::hex << this->header.signature << "\n";
    std::cout << "Dimensions: "; printImageSize();
    std::cout << "Size of a file: " << this->fileSize  * std::pow(10, -3) << "kB" << "\n";
}

/**
 * Helper method for efficient printing of image size
 */
void PPM::printImageSize() const {
    bool printX = false;
    for (int i = 0; i < 8; ++i) {
        if (i >= 4) {
            if (!printX) {
                std::cout << "x";
                printX = true;
            }
            std::cout << this->header.height[i - 4];
        } else {
            std::cout << this->header.width[i];
        }
    }
    std::cout << "\n";
}

void PPM::copyData(std::ifstream& input) {
    this->dataCopy = new unsigned char[this->dataSize];
    unsigned char value;
    input.seekg(0);

    for (int i = 0; i < this->dataSize; ++i) {
        value = (unsigned char) input.get();
        this->dataCopy[i] = value;
    }
}