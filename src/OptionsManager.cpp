#include <string>
#include <vector>

namespace fs = std::filesystem;

struct OptionsManager{
    private:
        fs::path file = fs::path("");
        const char* filename;
        std::string argument;
        std::string extension;

    
    public:
        OptionsManager(std::string argument, const char* path, std::string extension);
        void fileInformation();
        void manage();
        // void encrypt();
        // void decrypt();
        // void check();
};