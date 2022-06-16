#include "ExceptionHandler.cpp"
#include "OptionsHandler.cpp"
#include <iostream>
#include <string>

OptionsHandler::OptionsHandler(char** argv) {
    this->argument = argv[1];
    this->path = argv[2];
    this->extension = std::to_string(this->findExtension());
}

/**
 * @brief Checks if an argument is supported
 * 
 * @return true 
 * @return false 
 */

bool OptionsHandler::Validate_Argument() {
    for (const auto & possibleArgument : this->possibleArguments) {
        if (possibleArgument == this->argument) {
            return true;
        }
    }
    throw InvalidArgumentException();
}

/**
 * @brief Validates if an extension is within the capabilities of software
 * 
 * @return true 
 * @return false 
 */

bool OptionsHandler::Validate_Extension() {
    try {
        for (const auto & possibleFormat : this->possibleFormats) {
            if (possibleFormat == this->extension) {
                std::cout << "INFO: Extension found: " << this->extension << std::endl;
                return true;
            }
        }
        throw InvalidFormatException();
    } catch (const InvalidFormatException& e) {
        std::cout << e.what() << '\n';
        return false;
    }
}


/**
 * @brief Function to find the extension of file from a given path and if the extension is within the path
 * 
 * @return std::string 
 */

bool OptionsHandler::findExtension() {
    for (int i = 0; i < this->path.size(); i++) {
        if (this->path.at(i) == '.') {
            this->extension = path.substr(i, path.length() - 1);
            return true;
        }
    }
    throw FileNotFoundException();
}

std::string OptionsHandler::getArgument() {
    return this->argument;
}
