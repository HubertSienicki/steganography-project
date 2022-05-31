
struct Interface{
    public:
        bool init(int argc, char **argv);
        bool Validate(int argc, char **argv);
        std::string getExtension(char **argv);
        Interface();
};