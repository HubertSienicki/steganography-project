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
    std::ifstream input(this->filename,std::ios::binary);

    if (!input) {
        std::cerr << "Could not open a file";
    } else {
        this->readPPM(input);
        this->printPPMInfo();
    }
}

PPM::PPM(const char* filename, std::string message) {
    this->filename = filename;
    std::ifstream input(this->filename, std::ios::binary);

    if (!input) {
        std::cerr << "Could not open a file";
    } else {
        this->readPPM(input);
        this->copyData(input);
        this->encode(input, std::move(message));
        this->writePPM();
    }
}

PPM::PPM(const char* filename, int seed) {
    this->filename = filename;
    std::ifstream input(this->filename, std::ios::binary);

    if(!input){
        std::cerr << "Could not open a file";
    }else{
        this->readPPM(input);
        this->decode(input, seed);
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

        if (temp == '\n' || temp == ' ' || temp == '#') {
            index++;
            if (index == 4) {
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
void PPM::encode(std::ifstream& input, std::string message) {
    int messageLength = message.size();
    this->bitsToEncode = messageLength * 8;

    if (messageLength <= dataSize) {
        input.seekg(this->header.data_offset);
        this->bitSwitch(message, messageLength);
    }
}

void PPM::decode(std::ifstream& input, int seed) {
    int msgLength = seed/8;
    char decodedMessage[msgLength];

    std::bitset<8> currentChar;
    std::bitset<8> decodedChar;

    input.seekg(this->header.data_offset);

    for (int i = 0; i < msgLength; ++i) {
        for (int j = 0; j < 8; ++j) {
            currentChar = (std::bitset<8>) input.get();
            decodedChar[7 - j] = currentChar[0];
        }
        unsigned long longChar = decodedChar.to_ulong();
        auto c = static_cast<unsigned char>(longChar);
        decodedMessage[i] = c;
    }
        std::cout << "Decoded Message: ";

        for (int i = 0; i < msgLength; ++i) {
           std::cout << decodedMessage[i];
        }
    }

/**
 * Writes a new file containing encoded information
 */
void PPM::writePPM() const {
    std::ofstream file;
    file.open("C:\\Users\\kneiv\\CLionProjects\\steganography-project\\testDir\\xd3.ppm", std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "The file could not be rewritten \n.";
        return;
    } else {
        file.write(reinterpret_cast<char*>(this->dataCopy), this->dataSize);

        std::cout << "\n------------------------------------------ \n";
        std::cout << "File has been written successfully! \n"
                  << "Seed: " << this->generateSeed() << "\n";
        std::cerr << "INFO: PLEASE REMEMBER TO SAVE THE SEED AS IT IS IMPORTANT TO DECODE THE MESSAGE! \n";
        file.close();
        return;
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

    for (int i = 0; i < dataSize; ++i) {
        value = input.get();
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
        }
    }
}

int PPM::generateSeed() const {
    return this->bitsToEncode;
}

PPM::~PPM()= default;