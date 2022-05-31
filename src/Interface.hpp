#include "..\include\CLI11\include\CLI\CLI.hpp"
#include "Interface.cpp"
#include "OptionsHandler.hpp"
#include <string>
#include <iostream>
#include "OptionsManager.hpp"

std::string message = "Programme allowing the user to encrypt and decrypt \n messages using LSB insertion method \n";

Interface::Interface(){

}

/**
 * @brief 
 * Initializes CLI
 * @param argc 
 * @param argv 
 * @return true 
 * @return false 
 */

bool Interface::init(int argc, char **argv){
    CLI::App app{message};

    std::string filename = "default";

    app.add_option("-i, --info", "Information string");
    app.add_option("-e, --encrypt", "Encryption");
    app.add_option("-d, --decrypt", "Decryption");
    app.add_option("-c, --check", "Check");

    CLI11_PARSE(app, argc, argv);

    if(this->Validate(argc, argv)){ 
        OptionsManager manager(argv[1], argv[2], this->getExtension(argv));
        manager.fileInformation();
    }else{
        return 0;
    }

    return 0;
}

/**
 * @brief Combines methods from OptionHandler class to validate if a whole path leads to a file or not.
 * 
 * @param argc 
 * @param argv 
 * @return true 
 * @return false 
 */

bool Interface::Validate(int argc, char **argv){
    OptionsHandler handler(argc, argv);
    try
    {
        if(handler.Validate_Argument()){
            try
            {
                if(handler.findExtension()){
                    try
                    {
                        if(handler.Validate_Extension()){
                            return 1;
                        }
                    }
                    catch(const InvalidFormatException& e)
                    {
                        std::cerr << e.what() << '\n';
                    }                
                }
            }catch(const FileNotFoundException& e)
            {
                std::cerr << e.what() << '\n';
            }
                return 0;  
            }
    }
    catch(const InvalidArgumentException& e)
    {
        std::cerr << e.what(handler.getArgument()) << '\n';
        return 0;
    }
    return 0;
}

/**
 * @param argv arguments provided to the program
 * @return extension
 */
std::string Interface::getExtension(char **argv) {
    std::string path = argv[2];
    std::string extension;

    for (int i = 0; i < path.size(); i++)
    {
        if(path.at(i) == '.'){
            std::string extension;
            extension = path.substr(i, path.length() - 1);
            extension = extension;
            return extension;
        }
    }
    return NULL;
}