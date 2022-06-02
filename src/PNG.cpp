//
// Created by kneiv on 5/17/2022.
//

#include "PNG.h"
#include <fstream>


//Invokes read method by default
PNG::PNG(const char* filename) {
    this->filename = filename;

    std::ifstream input(this->filename);

    if (!input.is_open()) {
        std::cerr << "Could not open a file..."
                  << "\n";
    } else {
        this->readPNG(input);
    }
}

//Invokes encode by default
PNG::PNG(const char* filename, std::string message) {
    this->filename = filename;

    std::ifstream input(this->filename);

    if (!input.is_open()) {
        std::cerr << "Could not open a file..."
                  << "\n";
    } else {
        this->readPNG(input);
        this->encode(input, message);
    }
}

//Invoked decode by default
PNG::PNG(const char* filename, int seed) {
    this->filename = filename;

    std::ifstream input(this->filename);

    if (!input.is_open()) {
        std::cerr << "Could not open a file..."
                  << "\n";
    } else {
        this->readPNG(input);
        this->decode(input, seed);
    }
}