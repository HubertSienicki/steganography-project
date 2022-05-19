//
// Created by kneiv on 5/16/2022.
//

#include "BMP.h"
#include <iostream>
#include <fstream>
#include <cmath>

BMP::BMP(const char *fileName) {

}

/**
 * @brief Reads the contents of a bmp file
 * @param fileName Name of a bmp file
 * @return array of pixels
 */
#include "BMP.h"
#include <fstream>
#include <iostream>

BMP::BMP(const char *filename) {
    this->filename = filename;
    std::fstream input(this->filename);

    if(!input){
        std::cerr << "Could not open a file. Please try again and validate data \n";
    }else{
        this->readBMP(filename);
    }
}

unsigned int bmpFileHeader[14];
unsigned int bmpInfoHeader[124];
unsigned char temp;

void BMP::readBMP(const char *filename) {

    std::ifstream input(filename);
    this->readBMPFileHeader(input);
    this->readBMPInfoHeader(input);
    this->readBMPData(input);

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

void BMP::readBMPData(std::ifstream &input) {
    input.seekg(this->bmp_file_header.data_offset);
    data.resize(this->bmp_info_header.height * this->bmp_info_header.width);

    for (int i = 0; i < this->data.size() - 1; ++i) {
        temp = (unsigned char)input.get();
        data.push_back(temp);
    }

    for (int i = 0; i < this->data.size() - 1; ++i) {
        std::cout << std::hex << data.at(i) << " ";
    }

}

std::uint16_t BMP::getSignature() {
    return this->bmp_file_header.signature;
}