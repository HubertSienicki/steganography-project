//
// Created by kneiv on 6/15/2022.
//

#include "PPM.h"
#include <bitset>
#include <fstream>
#include <utility>
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
        this->encode(input, std::move(message));
    }
}

/**
 * Reads the bmp file;
 * @param input - input to a file
 */
void PPM::readPPM(std::ifstream& input) {
    int index = 0;//0->signature, 1-->width, 2-->height, 3-->Max color
    for (int i = 1; i > 0; ++i) {
        auto temp = (unsigned char) input.get();

        if (temp == '\n' || temp == ' ') {
            index++;
            if (i == 17) {
                this->header.data_offset = i;

                input.seekg(0, std::ios::end);
                this->fileSize = input.tellg();
                this->dataSize = fileSize * 8;

                return;
            }
        } else {
            switch (index) {
                case 0:
                    this->header.signature = (this->header.signature << 8) | temp;
                    break;
                case 1:
                    this->header.width[i - 4] = (this->header.width[i - 4] << 8) | temp;
                    break;
                case 2:
                    this->header.height[i - 9] = (this->header.height[i - 9] << 8) | temp;
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
}

/**
 * Prints information about .ppm file;
 */
void PPM::printPPMInfo() const {
    std::cout << "Dimensions: ";
    printImageSize();
    std::cout << "Size of a file: " << this->fileSize * std::pow(10, -3) << "kB"
              << "\n";
}

/**
 * Helper method for printing image size
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

/**
 * Encodes message to a data array
 * @param input - input to .ppm file
 * @param message - message to encode to a file
 */
void PPM::encode(std::ifstream& input, std::string message) const {
    int messageLength = message.size();
    int bitsToEncode = messageLength * 8;

    if (messageLength <= dataSize) {
        input.seekg(this->header.data_offset);

        std::bitset<8> toEncode[bitsToEncode];

        for (int i = 0; i < bitsToEncode; ++i) {
            toEncode[i] = this->dataCopy[this->header.data_offset + i];
            std::cout << toEncode[i] << " ";
        }
        std::cout << "\n\n";

        this->bitSwitch(message, messageLength);
    }
}

/**
 * Writes a new file containing encoded information
 */
void PPM::writePPM() const {
    std::ofstream file;
    file.open("C:\\Users\\kneiv\\CLionProjects\\steganography-project\\testDir\\testPPMPPM.ppm", std::iostream::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "The file could not be rewritten \n.";
        return;
    } else {
        file.write(reinterpret_cast<char*>(this->dataCopy), this->dataSize);
    }
}

/**
 * Copies data from .ppm file to a data array
 * @param input - input to a file
 */
void PPM::copyData(std::ifstream& input) {
    this->dataCopy = new unsigned char[this->dataSize];
    unsigned char value;
    input.seekg(0);

    for (int i = 0; i < this->dataSize; ++i) {
        value = (unsigned char) input.get();
        this->dataCopy[i] = value;
    }
}

/**
 * Changes last bit of each byte in the data array according to the letters of a message
 * @param message - message to encode to the data array
 * @param messageLength -
 * length of that message
 */
void PPM::bitSwitch(std::string message, int messageLength) const {
    int bitMask = (1 << 0);

    for (int i = 0; i < messageLength; ++i) {
        std::bitset<8> charBinary(message[i]);
        for (int j = 0; j < 8; ++j) {
            if (charBinary[7 - j] == 0) {
                this->dataCopy[this->header.data_offset + 8 * i + j] = ((this->dataCopy[this->header.data_offset + 8 * i + j]) & ~bitMask);//change to zero last position
            } else {
                this->dataCopy[this->header.data_offset + 8 * i + j] = ((this->dataCopy[this->header.data_offset + 8 * i + j]) & ~bitMask | (1 << 0));//change to 1 last position
            }
            std::cout <<  (std::bitset<8>)this->dataCopy[this->header.data_offset + 8 * i + j] << " ";
        }
    }
}