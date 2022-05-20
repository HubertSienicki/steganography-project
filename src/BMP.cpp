//
// Created by kneiv on 5/17/2022.
//

#include "BMP.h"
#include <fstream>
#include <iostream>
#include <bitset>

BMP::BMP(const char *filename) {
    this->filename = filename;
    std::ifstream input(this->filename);

    if(!input){
        std::cerr << "Could not open a file. Please try again. \n";
    }else{
        this->readBMP(filename);
        this->encodeMessage(input, "a");
    }
}

unsigned int bmpFileHeader[14];
unsigned int bmpInfoHeader[124];
unsigned char temp;

void BMP::readBMP(const char *filename) {

    std::ifstream input(filename);
    this->readBMPFileHeader(input);
    this->readBMPInfoHeader(input);
}

/**
 * @brief function staticly reads a file header of a bmp file
 *
 * @param input ifstream of a file
 */

void BMP::readBMPFileHeader(std::ifstream& input) {
    for(int i =0;i<14;i++) {
        temp = (unsigned char)input.get();
        bmpFileHeader[i] = temp;
    }

    this->bmp_file_header.signature = (bmpFileHeader[0] << 8) | bmpFileHeader[1];
    this->bmp_file_header.fileSize = (((bmpFileHeader[5] << 8) | bmpFileHeader[4]) << 8 | bmpFileHeader[3]) << 8 | bmpFileHeader[2];
    this->bmp_file_header.data_offset = (((bmpFileHeader[13] << 8) | bmpFileHeader[12]) << 8 | bmpFileHeader[11]) << 8 | bmpFileHeader[10];
    this->dataSize = this->bmp_file_header.fileSize * 8;
}

/**
 * @brief funciton reads bmp informaiton header
 *
 * @param input ifstream of a file
 */

void BMP::readBMPInfoHeader(std::ifstream &input) {
    for(int i = 0;i<124;i++) {
        temp = (unsigned char)input.get();
        bmpInfoHeader[i] = temp;
    }

    this->bmp_info_header.header_size = (((bmpInfoHeader[3] << 8) | bmpInfoHeader[2]) << 8 | bmpInfoHeader[1]) << 8 | bmpInfoHeader[0];
    this->bmp_info_header.width = (((bmpInfoHeader[7] << 8) | bmpInfoHeader[6]) << 8 | bmpInfoHeader[5]) << 8 | bmpInfoHeader[4];
    this->bmp_info_header.height = (((bmpInfoHeader[11] << 8) | bmpInfoHeader[10]) << 8 | bmpInfoHeader[9]) << 8 | bmpInfoHeader[8];
    this->bmp_info_header.planes = (bmpInfoHeader[13] << 8) | bmpInfoHeader[12];
    this->bmp_info_header.bits_per_pixel = (bmpInfoHeader[15] << 8) | bmpInfoHeader[14];
    this->bmp_info_header.compression = (((bmpInfoHeader[19] << 8) | bmpInfoHeader[18]) << 8 | bmpInfoHeader[17]) << 8 | bmpInfoHeader[16];
    this->bmp_info_header.image_size = (((bmpInfoHeader[23] << 8) | bmpInfoHeader[22]) << 8 | bmpInfoHeader[21]) << 8 | bmpInfoHeader[20];
}



void BMP::encodeMessage(std::ifstream &input, std::string message) {

    int messageLength = message.size();
    int stride = 3;
    int pixelSize = 0;

    input.seekg(this->bmp_file_header.data_offset);

    switch(this->bmp_info_header.bits_per_pixel){
        case 24:
            pixelSize = 3;
            break;
        default:
            std::cerr << "This format of a BitMap is not usable in this programme. Please, make sure you use 24bit BitMap.";
            break;
    }

    this->copyData(input);

//    for (int i = 1; i < messageLength; ++i) {
//        this->dataCopy[bmp_file_header.data_offset + (3*i-1)] = message.at(i-1);
//    }

    input.close();

    std::bitset<8> charBinary(message[0]);
    std::cout << charBinary;
    std::bitset<8> pixelsToEncode[charBinary.size()];
    std::cout << "\n";

    for (int i = 0; i < charBinary.size(); ++i) {
        std::bitset<8> pixelBinary(this->dataCopy[this->bmp_file_header.data_offset + i]);
        if(pixelBinary[7 - i] != charBinary[7 - i]){
            pixelBinary = pixelBinary << 1;
            std::cout << pixelBinary << " ";
        }else{
            std::cout << pixelBinary << " ";
        }
    }

    //this->writeBitmap();
}

void BMP::writeBitmap() {
    std::ofstream file;
    file.open("C:\\Users\\kneiv\\CLionProjects\\untitled\\test.bmp", std::ios::out | std::ios::binary);

    if(!file.is_open()){
        std::cerr << "New file could not be created.";
        return;
    }else{
        file.write(reinterpret_cast<char*>(this->dataCopy), this->dataSize);

        std::cout << "File has been written succesfully!";
        file.close();
        return;
    }
}


//HELPER METHOD

/**
 * @brief copies a whole bitmap
 * @param input
 */

void BMP::copyData(std::ifstream &input) {
    this->dataCopy = new unsigned char[dataSize];
    unsigned int value = 0;

    input.seekg(0);

    for (int i = 0; i < dataSize; ++i) {
        value = (unsigned char)input.get();
        this->dataCopy[i] = value;
    }
}