#include "..\include\CLI11\include\CLI\CLI.hpp"
#include "Interface.cpp"
#include "OptionsHandler.hpp"
#include "OptionsManager.hpp"
#include <iostream>
#include <string>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wstring-compare"

Interface::Interface() = default;

/**
 * @brief 
 * Initializes CLI
 * @param argc 
 * @param argv 
 * @return true 
 * @return false 
 */

bool Interface::init(int argc, char** argv) {
    CLI::App app{"Program allowing the user to encrypt and decrypt \n messages using LSB insertion method \n"};

    std::pair<std::string, std::string> args;

    app.add_option("-i, --info", "Prints information about a provided file. \nUSAGE: ./steganography_project.exe -i *\"path/to/file\"*")->expected(1);
    app.add_option("-e, --encrypt", "Encryption")->expected(2);
    app.add_option("-d, --decrypt", "Decryption")->expected(2);
    app.add_option("-c, --check", "Check")->expected(2);

    CLI11_PARSE(app, argc, argv)

    /**
     * @fixed made code below less ugly
     */
    if ((argv[2] == nullptr || argv[2] == "") && (argv[1] != "-h" || argv[1] != "--help")) {
        std::cerr << "ERROR: Provided path is empty. Please provide a path to the file you wish to encode to a file."
                  << "\n";
        return false;
    } else {
        if (Interface::Validate(argv)) {

            std::string currentArg = argv[1];//easier comparison.
            OptionsManager manager(currentArg, argv[2], Interface::getExtension(argv));

            if (currentArg == "-i" || currentArg == "--info") {
                manager.fileInformation();
                return false;

            } else if (currentArg == "-e" || currentArg == "--encrypt") {

                if (argv[3] == nullptr || argv[3] == "") {

                    std::cerr << "ERROR: Empty encryption message...";
                    return false;

                } else {
                    manager.encrypt(argv[3]);
                    return false;
                }
            } else if (currentArg == "-d" || currentArg == "--decrypt") {

                if (argv[3] == nullptr || argv[3] == "") {

                    std::cerr << "ERROR: Empty seed needed for decryption...";
                    return false;

                } else {

                    int seed = std::stoi(argv[3]);
                    manager.decrypt(seed);
                    return false;
                }
            }
            if (currentArg == "-c" | currentArg == "--check") {
                if (argv[3] == nullptr || argv[3] == "") {

                    std::cerr << "ERROR: Empty message needed for checking...";
                    return false;

                } else {
                    manager.check(argv[3]);
                    return false;
                }
            }
        } else {
            return false;
        }
    }
    return false;
}

/**
 * @brief Combines methods from OptionHandler class to validate if a whole path leads to a file or not.
 * @param argv argument values
 * @return true if validation completes
 * @return false if validation was incomplete
 */

bool Interface::Validate(char** argv) {
    OptionsHandler handler(argv);
    try {
        if (handler.Validate_Argument()) {
            try {
                if (handler.findExtension()) {
                    try {
                        if (handler.Validate_Extension()) {
                            return true;
                        }
                    } catch (const InvalidFormatException& e) {
                        std::cerr << e.what() << '\n';
                    }
                }
            } catch (const FileNotFoundException& e) {
                std::cerr << e.what() << '\n';
            }
            return false;
        }
    } catch (const InvalidArgumentException& e) {
        std::cerr << InvalidArgumentException::what(handler.getArgument()) << '\n';
        return false;
    }
    return false;
}

/**
 * @param argv argument values
 * @return std::string extension extension from the end of path
 */
std::string Interface::getExtension(char** argv) {
    std::string path = argv[2];
    std::string extension;

    for (int i = 0; i < path.size(); i++) {
        if (path.at(i) == '.') {
            extension = path.substr(i, path.length() - 1);
            extension = extension;
            return extension;
        }
    }
    return "nullptr";
}
#pragma clang diagnostic pop