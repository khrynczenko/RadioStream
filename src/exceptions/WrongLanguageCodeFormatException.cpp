#include "../../include/exceptions/WrongLanguageCodeFormatException.hpp"

WrongLanguageCodeFormatException::WrongLanguageCodeFormatException(std::string_view code)
{
    message_ = "Code length is not correct. In case of ISO 639-1 it should be a 2 letter identifier."
        "But " + std::string(code) + " is " + std::to_string(code.length()) + "letters.";
}

char const* WrongLanguageCodeFormatException::what() const
{
    return message_.c_str();
}
