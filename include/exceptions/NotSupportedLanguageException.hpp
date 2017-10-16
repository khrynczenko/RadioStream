#ifndef NOTSUPPORTEDLANGUAGEEXCEPTION_H
#define NOTSUPPORTEDLANGUAGEEXCEPTION_H

#include <exception>
#include <string>
class NotSupportedLanguageException : public std::exception
{
public:
    NotSupportedLanguageException(const std::string& language);
    char const* what() const override;
private:
    std::string message_;
};

#endif
