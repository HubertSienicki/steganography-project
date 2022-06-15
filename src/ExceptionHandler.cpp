#include <exception>

struct InvalidFormatException : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Invalid file format. Please try again with the following formats: [.bmp, .ppm]";
    }
};

struct FileNotFoundException : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "File not found. Please validate the path and try again.";
    }
};

struct InvalidArgumentException : public std::exception {
public:
    static std::string what(const std::string& argument) noexcept {
        return "The argument: " + argument + " you provided was not expected.";
    }
};
