#ifndef WRONGLANGUAGECODEFORMATXCEPTION_H
#define WRONGLANGUAGECODEFORMATXCEPTION_H

#include <exception>
#include <string>
#include "../Language.hpp"

class WrongLanguageCodeFormatException : public std::exception
{
public:
    WrongLanguageCodeFormatException(std::string_view code);
    char const* what() const override;
private:
    std::string message_;

};

#endif
