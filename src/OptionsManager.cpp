#include <string>
#include <vector>

namespace fs = std::filesystem;

struct OptionsManager{
    private:
        fs::path file = fs::path("");
        std::string argument;

    
    public:
        OptionsManager(std::string argument, std::string path);
        void fileInformation();
        void manage();
        // void encrypt();
        // void decrypt();
        // void check();
};