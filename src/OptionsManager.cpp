#include <string>
#include <vector>


struct OptionsManager{
    private:
        std::string path = "";
        std::string argument;
        std::string extension;
        std::string filename;

    
    public:
        OptionsManager(std::string argument, std::string path, std::string extension);
        void fileInformation();
        void manage();
        // void encrypt();
        // void decrypt();
        // void check();

};