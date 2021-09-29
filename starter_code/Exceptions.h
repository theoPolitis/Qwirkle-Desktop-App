#ifndef ASSIGN2_EXCEPTIONS_H
#define ASSIGN2_EXCEPTIONS_H

#include <exception>

// Exception thrown when SerialisedData method is called when the mode
// disallows it
class invalid_mode_exception : public std::exception {
    const char* what() const noexcept override {
        return "invalid_mode_exception";
    }
};

// Exception thrown when SerialisedData is constructed in read only mode, 
// but the file it's pointing to doesn't exist
class file_not_found_exception : public std::exception {
    const char* what() const noexcept override {
        return "file_not_found_exception";
    }
};

#endif //ASSIGN2_EXCEPTIONS_H