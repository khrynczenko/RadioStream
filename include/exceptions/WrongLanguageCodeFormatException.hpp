#ifndef WRONGLANGUAGECODEFORMATXCEPTION_H
#define WRONGLANGUAGECODEFORMATXCEPTION_H

#include <exception>
#include <string>

class WrongLanguageCodeFormatException : public std::exception {
   public:
    WrongLanguageCodeFormatException(std::string_view code);
    char const* what() const noexcept override;

   private:
    std::string message_;
};

#endif
