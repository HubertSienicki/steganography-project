#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-interfaces-global-init"

#include "BMP.h"
#include "OptionsManager.cpp"
#include "PPM.h"
#include <chrono>
#include <iostream>
#include <utility>

/**
 * @brief Helper method for printing last date modified
 */
auto print_last_write_time = [](fs::file_time_type const& fileTime) -> void {
    std::time_t currentFileTime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(fileTime));
    std::cout << "LAST MODIFIED: " << std::asctime(std::localtime(&currentFileTime)) << "\n";
};


OptionsManager::OptionsManager(std::string argument, const char* pathToFile, std::string extension) {
    this->file = fs::path(pathToFile);
    this->filename = pathToFile;
    this->argument = std::move(argument);
    this->extension = std::move(extension);
}

/**
 * @brief Displays information about a file
 */
void OptionsManager::fileInformation() {
    std::cout << "FILE NAME: " << this->file.filename() << "\n";

    if (this->extension == ".bmp") {
        BMP bitMap(this->filename);
        bitMap.printBitMapInformation();
    } else if (this->extension == ".ppm") {
        PPM ppm(this->filename);
        ppm.printPPMInfo();
    }
    auto fileTime = fs::last_write_time(this->file);
    print_last_write_time(fileTime);
}

/**
 * @brief calls for en encoding constructor
 * @param message message to encode
 */
void OptionsManager::encrypt(std::string message) {
    if(this->extension == ".bmp"){
        (BMP(this->filename, std::move(message)));
    }else if(this->extension == ".ppm"){
        (PPM(this->filename, message));
    }
}

/**
 * @brief calls for a decoding constructor
 * @param seed seed needed for decryption
 */
void OptionsManager::decrypt(int seed) {
    if (this->extension == ".bmp") {
        (BMP(this->filename, seed));
    }else if(this->extension == ".ppm"){
        (PPM(this->filename, seed));
    }
}

/**
 * Calls method check
 * @refitem
 * @param message message to check
 */
void OptionsManager::check(const std::string& message) {
    if(this->extension == ".bmp"){
        BMP bmp(this->filename);
        bmp.check(message);
    }else if(this->extension == ".ppm"){
        PPM ppm(this->filename);
        ppm.check(message);
    }
}

#pragma clang diagnostic pop