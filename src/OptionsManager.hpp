#include "BMP.h"
#include "OptionsManager.cpp"
#include <chrono>
#include <iostream>
#include <utility>


/**
 * @brief Helper method for printing last date modified
 */
auto print_last_write_time = [](fs::file_time_type const &fileTime) -> void {
    std::time_t currentFileTime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(fileTime));
    std::cout << "LAST MODIFIED: " << std::asctime(std::localtime(&currentFileTime)) << "\n";
};
//----------------//

OptionsManager::OptionsManager(std::string argument, const char *pathToFile, std::string extension) {
    this->file = fs::path(pathToFile);
    this->filename = pathToFile;
    this->argument = std::move(argument);
    this->extension = std::move(extension);
}

/**
 * @brief Displays information about a file
 */
void OptionsManager::fileInformation() {
    std::cout << "Argument: " << this->argument << "\n";
    std::cout << "FILE NAME: " << this->file.filename() << "\n";

    if (this->extension == ".bmp") {
        BMP bitMap(this->filename);
        bitMap.printBitMapInformation();
    }
    auto fileTime = fs::last_write_time(this->file);
    print_last_write_time(fileTime);
}

/**
 * @brief calls for en encoding constructor
 * @param seed
 */

void OptionsManager::encrypt(std::string message) {
    BMP bitmap(this->filename, message);
}

/**
 * @brief calls for a decoding constructor
 * @param seed
 */
void OptionsManager::decrypt(int seed) {
    BMP bitmap(this->filename, seed);
}
