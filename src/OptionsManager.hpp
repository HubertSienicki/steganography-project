#include "OptionsManager.cpp"
#include <iostream>
#include <fstream>



OptionsManager::OptionsManager(std::string argument, std::string path, std::string extension){
    this->path = path;
    this->argument = argument;
    this->extension = extension;
    this->filename = path.substr();
}


