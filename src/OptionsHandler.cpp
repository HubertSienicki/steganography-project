#include <string>
#include <vector>

struct OptionsHandler{
    private:
        std::string path;
        std::string extension;
        std::string argument;
        std::vector<std::string> const possibleFormats = {".png", ".jpg", ".jpeg", ".gif", ".bmp", ".txt"};
        std::vector<std::string> const possibleArguments = {"-i", "--info", "-e", "--encrypt", "-d", "--decrypt", "-c", "--check"};


    public:
        OptionsHandler(int argc, char **argv);

    bool Validate_Extension();
        bool findExtension();
        bool Validate_Argument();
        
        //Getters
        std::string getExtension();
        std::string getArgument();
        std::string getPath();

};