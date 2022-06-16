#pragma clang diagnostic push
#pragma ide diagnostic ignored "NullDereference" // no pointer-may-be-null for dataCopy table;
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions" // no narrowing conversions warnings
//
// Created by kneiv on 6/15/2022.
//

#include "PPM.h"
#include <bitset>
#include <fstream>
#include <valarray>

PPM::PPM(const char* filename) {
    this->filename = filename;
    std::ifstream input(this->filename, std::ios::binary);

    if (!input) {
        std::cerr << "Could not open a file. Please validate the path and try again. \n"
                  << "Aborting...";
        std::exit(1);
    } else {
        this->readPPM(input);
        input.close();
    }
}

PPM::PPM(const char* filename, const std::string& message) {
    this->filename = filename;
    std::ifstream input(this->filename, std::ios::binary);

    if (!input) {
        std::cerr << "Could not open a file. Please validate the path and try again. \n"
                  << "Aborting...";
        std::exit(1);
    } else {
        this->readPPM(input);
        this->copyData(input);
        this->encode(input, message);
        this->writePPM();
        input.close();
    }
}

PPM::PPM(const char* filename, int seed) {
    this->filename = filename;
    std::ifstream input(this->filename, std::ios::binary);

    if (!input) {
        std::cerr << "Could not open a file. Please validate the path and try again. \n"
                  << "Aborting...";
        std::exit(1);
    } else {
        this->readPPM(input);
        this->decode(input, seed);
        input.close();
    }
}

/**
 * Reads the bmp file;
 * @param input - input to a file
 */
void PPM::readPPM(std::ifstream& input) {
    int index = 0;//0->signature, 1-->width, 2-->height, 3-->Max color
    int tableIndex = 0;
    for (int i = 1; i > 0; ++i) {
        auto temp = (unsigned char) input.get();

        if (temp == '\n' || temp == ' ' || temp == '#') {
            index++;
            tableIndex = 0;
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
                    this->header.width[tableIndex] = (this->header.width[tableIndex] << 8) | temp;
                    tableIndex++;
                    break;
                case 2:
                    this->header.height[tableIndex] = (this->header.height[tableIndex] << 8) | temp;
                    tableIndex++;
                    break;
                case 3:
                    this->header.colorMax[tableIndex] = (this->header.colorMax[tableIndex] << 8) | temp;
                    tableIndex++;
                    break;
                default:
                    std::cerr << "There was a problem with reading .ppm file. ";
                    std::exit(1);
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
    std::cout << "Color mask: " << this->header.colorMax << "\n";
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
            if (this->header.height[i - 4] != '\000') {
                std::cout << this->header.height[i - 4];
            }
        } else {
            if (this->header.width[i] != '\000') {
                std::cout << this->header.width[i];
            }
        }
    }
    std::cout << "\n";
}

/**
 * Encodes message to a data array
 * @param input - input to .ppm file
 * @param message - message to encode to a file
 */
void PPM::encode(std::ifstream& input, const std::string& message) {
    int messageLength = message.size();
    this->bitsToEncode = messageLength * 8;

    if (messageLength <= dataSize) {
        input.seekg(this->header.data_offset);
        this->bitSwitch(message, messageLength);
    }
}

/**
 * Decodes a message using a provided seed
 * @param input - input to a file
 * @param seed - seed to decode a message
 */
void PPM::decode(std::ifstream& input, int seed) const {
    int msgLength = seed / 8;
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
        std::exit(1);
        return;
    } else {
        file.write(reinterpret_cast<char*>(this->dataCopy), this->dataSize);

        std::cout << "------------------------------------------ \n";
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

/**
 * @return generated seed
 */
int PPM::generateSeed() const {
    return this->bitsToEncode;
}

/**
 * Checks if a message will fit into bytes of a portable pixel map
 */
void PPM::check(const std::string& message) const {
    if (this->dataSize < message.size() * 8) {
        std::cerr << "WARNING: The message is too big for provided photo: " << this->filename;
    } else {
        std::cout << "This message \"" << message << "\" could be encoded inside this file: " << this->filename;
    }
}

PPM::~PPM() = default;
#pragma clang diagnostic pop