#ifndef EXCEPTIONS_LIB
#define EXCEPTIONS_LIB

#include <exception>
#include <string>

class ParseError : public std::exception {
    public:
        HeaderError(const std::string& msg);
        const char* what() const throw();
    private:
        std::string msg_;
};

#endif
