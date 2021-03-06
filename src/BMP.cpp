#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
//
// Created by kneiv on 5/17/2022.
//

#include "BMP.h"
#include <bitset>
#include <iostream>
#include <utility>
#include <valarray>

unsigned int bmpFileHeader[14]; //temporary holder for file header
unsigned int bmpInfoHeader[124];//temporary holder for info header
unsigned char temp;             //temp for holding data from a bitmap


//Constructor invokes read method.
BMP::BMP(const char* filename) {
    this->filename = filename;
    std::ifstream input(this->filename, std::ios::binary);

    if (!input) {
        std::cerr << "Could not open a file. Please validate the path and try again. \n";
        std::exit(1);
    } else {
        this->readBMP(filename);
    }
}

//Encode
BMP::BMP(const char* filename, std::string message) {
    this->filename = filename;
    std::ifstream input(this->filename, std::ios::binary);

    if (!input) {
        std::cerr << "Could not open a file. Please validate the path and try again. \n";
        std::exit(1);
    } else {
        this->readBMP(filename);
        this->encodeMessage(input, std::move(message));
    }
}

//Decode
BMP::BMP(const char* filename, int seed) {
    this->filename = filename;
    std::ifstream input(this->filename, std::ios::binary);

    if (!input) {
        std::cerr << "Could not open a file. Please validate the path and try again. \n";
        std::exit(1);
    } else {
        this->readBMP(filename);
        this->decodeMessage(input, seed);
    }
}


/**
 * @brief Combines both bmp
 * @param path path to a file
 */
void BMP::readBMP(const char* path) {

    std::ifstream input(path);
    this->readBMPFileHeader(input);
    this->readBMPInfoHeader(input);
}

/**
 * @brief Reads a file header of a bmp file
 * @param input InputFileStream of a file
 */
void BMP::readBMPFileHeader(std::ifstream& input) {
    for (unsigned int& i: bmpFileHeader) {
        temp = (unsigned char) input.get();
        i = temp;
    }

    this->bmp_file_header.signature = (bmpFileHeader[0] << 8) | bmpFileHeader[1];
    this->bmp_file_header.fileSize = (((bmpFileHeader[5] << 8) | bmpFileHeader[4]) << 8 | bmpFileHeader[3]) << 8 | bmpFileHeader[2];
    this->bmp_file_header.data_offset = (((bmpFileHeader[13] << 8) | bmpFileHeader[12]) << 8 | bmpFileHeader[11]) << 8 | bmpFileHeader[10];
    this->dataSize = this->bmp_file_header.fileSize * 8;
}

/**
 * @brief Reads bmp information header
 * @param input InputFileStream of a file
 */

void BMP::readBMPInfoHeader(std::ifstream& input) {
    for (unsigned int& i: bmpInfoHeader) {
        temp = (unsigned char) input.get();
        i = temp;
    }

    this->bmp_info_header.header_size = (((bmpInfoHeader[3] << 8) | bmpInfoHeader[2]) << 8 | bmpInfoHeader[1]) << 8 | bmpInfoHeader[0];
    this->bmp_info_header.width = (((bmpInfoHeader[7] << 8) | bmpInfoHeader[6]) << 8 | bmpInfoHeader[5]) << 8 | bmpInfoHeader[4];
    this->bmp_info_header.height = (((bmpInfoHeader[11] << 8) | bmpInfoHeader[10]) << 8 | bmpInfoHeader[9]) << 8 | bmpInfoHeader[8];
    this->bmp_info_header.planes = (bmpInfoHeader[13] << 8) | bmpInfoHeader[12];
    this->bmp_info_header.bits_per_pixel = (bmpInfoHeader[15] << 8) | bmpInfoHeader[14];
    this->bmp_info_header.compression = (((bmpInfoHeader[19] << 8) | bmpInfoHeader[18]) << 8 | bmpInfoHeader[17]) << 8 | bmpInfoHeader[16];
    this->bmp_info_header.image_size = (((bmpInfoHeader[23] << 8) | bmpInfoHeader[22]) << 8 | bmpInfoHeader[21]) << 8 | bmpInfoHeader[20];
}

/**
 * @brief Encodes the message to a copied bitmap
 * @param input input stream to a BitMap
 * @param message message to encode
 */

void BMP::encodeMessage(std::ifstream& input, std::string message) {

    int messageLength = message.size();
    this->bitsToEncode = messageLength * 8;// Every letter is 8 bits, hence the table size will is msg length * 8

    if (this->bmp_info_header.bits_per_pixel == 24) {
        if (messageLength <= this->dataSize) {
            input.seekg(this->bmp_file_header.data_offset);

            this->copyData(input);

            input.close();

            std::bitset<8> toEncode[bitsToEncode];// for easier read data will be encoded to a set of binary letters

            for (int j = 0; j < bitsToEncode; ++j) {
                toEncode[j] = this->dataCopy[this->bmp_file_header.data_offset + j];// filling a table ofbits for encoding;
            }

            for (int i = 0; i < messageLength; ++i) {
                std::bitset<8> charBinary(message[i]);// binary representation of a letter in a message;
                for (int j = 0; j < 8; ++j) {
                    if (charBinary[7 - j] != toEncode[8 * i + j][7]) {
                        this->dataCopy[this->bmp_file_header.data_offset + 8 * i + j] = this->dataCopy[this->bmp_file_header.data_offset + 8 * i + j] << 1;
                    }
                }
            }
            this->writeBitmap();
        } else {
            std::cerr << "The message does not fit inside this BitMap.";
            std::exit(1);
        }
    } else {
        std::cerr << "BitMap is not supported for " << this->bmp_info_header.bits_per_pixel << " bits, please try again with a 24 bit BitMap. \n";
        std::exit(1);
    }
}

/**
 * @brief writes a bitmap to a new file
 */
void BMP::writeBitmap() const {
    std::ofstream file;
    file.open("C:\\Users\\kneiv\\CLionProjects\\steganography-project\\testDir\\test.bmp", std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "New file could not be created. \n";
        std::exit(1);
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
 * @brief Decodes message bit by bit using a previously generated seeds.
 * @param input Input to a .bmp file;
 * @param seed Generated seed for decoding message.
 */
void BMP::decodeMessage(std::ifstream& input, int seed) const {

    int msgLength = seed / 8;
    char decodedMessage[msgLength];

    std::bitset<8> currentChar;
    std::bitset<8> decodedChar;
    input.seekg(this->bmp_file_header.data_offset);

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
 * @brief Prints bitmap information
 */
void BMP::printBitMapInformation() const {
    std::cout << "Size of a bitmap: " << this->bmp_file_header.fileSize * std::pow(10, -3) << " kB"
              << "\n";
    std::cout << "Dimensions of a bitmap: " << this->bmp_info_header.width << "x" << this->bmp_info_header.height << " (pixels) "
              << "\n";
    std::cout << "Format: " << this->bmp_info_header.bits_per_pixel << " bits"
              << "\n";
}

/**
 * @brief copies a whole bitmap
 * @param input
 */
void BMP::copyData(std::ifstream& input) {
    this->dataCopy = new unsigned char[this->dataSize];
    unsigned int value;

    input.seekg(0);

    for (int i = 0; i < dataSize; ++i) {
        value = (unsigned char) input.get();
        this->dataCopy[i] = value;
    }
}

/**
 * @brief Returns seed for a bitmap
 * @return int bitsToEncode as seed;
 */
int BMP::generateSeed() const {
    return this->bitsToEncode;
}

/**
 * Checks if a message will fit into bytes of a bitmap
 */
void BMP::check(const std::string& message) const {
    if (this->dataSize < message.length() * 8) {
        std::cerr << "WARNING: The message is too big for provided photo: " << this->filename;
    } else {
        std::cout << "This message \"" << message << "\" could be encoded inside this file: " << this->filename;
    }
}

#pragma clang diagnostic pop