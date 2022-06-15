
struct Interface {
public:
    static bool init(int argc, char** argv);
    static bool Validate(int argc, char** argv);
    static std::string getExtension(char** argv);
    Interface();
};