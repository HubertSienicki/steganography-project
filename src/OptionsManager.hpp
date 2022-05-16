#include "OptionsManager.cpp"
#include <iostream>
#include <filesystem>
#include <chrono>

namespace fs = std::filesystem;


//HELPER
auto print_last_write_time = [](fs::file_time_type const &fileTime) -> void {
    std::time_t currentFileTime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(fileTime));
    std::cout << "LAST MODIFIED: " << std::asctime(std::localtime(&currentFileTime));
};
//----------------//

OptionsManager::OptionsManager(std::string argument, std::string pathToFile){
    this->file = fs::path(pathToFile);
    this->argument = argument;
}

/**
 * @brief Displays information about a file
 */
void OptionsManager::fileInformation() {
    std::cout << "FILE NAME: " << this->file.filename() << std::endl;
    std::cout << "FILE SIZE: " << file_size(this->file) << " bits" << std::endl;

    auto fileTime = fs::last_write_time(this->file);
    print_last_write_time(fileTime);

}



