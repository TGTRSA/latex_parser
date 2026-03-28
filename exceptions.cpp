#include "exceptions.h"

ParseError::ParseError(const std::string& msg) : msg_(msg) {}
const char* ParseError::what() const throw() {
    return msg_.c_str();
}
