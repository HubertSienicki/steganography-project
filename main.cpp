#include <iostream>
#include <string>
#include "src/Interface.hpp"
#include "src/OptionsManager.hpp"



int main(int argc, char **argv){
    std::string tempArg = argv[1];

    if((argv[1] == nullptr || argv[1] == "" ) && (tempArg != "-h" || tempArg != "--help")){
        std::cout << "Provided path is empty. Please provide a path to the file you wish to encode to a file." << std::endl;
        return 0;
    }else{
        Interface mainInt;
        mainInt.init(argc, argv);
    }
    return 0;
}