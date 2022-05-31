#include "ExceptionHandler.cpp"
#include "OptionsHandler.cpp"
#include <iostream>
#include <string>

OptionsHandler::OptionsHandler(int argc, char **argv) {
    this->argument = argv[1];
    this->path = argv[2];
    this->extension = this->findExtension();
}

/**
 * @brief Checks if an argument is supported
 * 
 * @return true 
 * @return false 
 */

bool OptionsHandler::Validate_Argument() {
    for (int i = 0; i < this->possibleArguments.size(); i++) {
        if (this->possibleArguments.at(i) == this->argument) {
            return 1;
        }
    }
    throw InvalidArgumentException();
    return 0;
}

/**
 * @brief Validates if an extension is within the capabilities of software
 * 
 * @return true 
 * @return false 
 */

bool OptionsHandler::Validate_Extension() {
    try {
        for (int i = 0; i < this->possibleFormats.size(); i++) {
            if (this->possibleFormats.at(i) == this->extension) {
                std::cout << "INFO: Extension found: " << this->extension << std::endl;
                return 1;
            }
        }
        throw InvalidFormatException();
    } catch (const InvalidFormatException &e) {
        std::cout << e.what() << '\n';
        return 0;
    }

    return 0;
}


/**
 * @brief Function to find the extension of file from a given path and if the extension is within the path
 * 
 * @return std::string 
 */

bool OptionsHandler::findExtension() {
    for (int i = 0; i < this->path.size(); i++) {
        if (this->path.at(i) == '.') {
            std::string extension;
            extension = path.substr(i, path.length() - 1);
            this->extension = extension;
            return 1;
        }
    }
    throw FileNotFoundException();
}

//GETTERS
std::string OptionsHandler::getExtension() {
    return this->extension;
}

std::string OptionsHandler::getArgument() {
    return this->argument;
}

std::string OptionsHandler::getPath() {
    return this->path;
}
