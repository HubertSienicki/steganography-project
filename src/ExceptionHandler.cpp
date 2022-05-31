#include <exception>

struct InvalidFormatException : public std::exception {
public:
    const char *what() const throw() {
        return "Invalid file format. Please try again with the following formats: [.png, .jpg, .jpeg, .gif, .bmp]";
    }
};

struct FileNotFoundException : public std::exception {
public:
    const char *what() const throw() {
        return "File not found. Please validate the path and try again.";
    }
};

struct InvalidArgumentException : public std::exception {
public:
    std::string what(std::string argument) const throw() {
        return "The argument: " + argument + " you provided was not expected.";
    }
};
