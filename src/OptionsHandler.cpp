#include <string>
#include <vector>

class OptionsHandler {
private:
    std::string path;
    std::string extension;
    std::string argument;
    std::vector<std::string> const possibleFormats = {".bmp", ".ppm"};
    std::vector<std::string> const possibleArguments = {"-i", "--info", "-e", "--encrypt", "-d", "--decrypt", "-c", "--check"};


public:
    explicit OptionsHandler(char** argv);

    bool Validate_Extension();
    bool findExtension();
    bool Validate_Argument();

    std::string getArgument();
};