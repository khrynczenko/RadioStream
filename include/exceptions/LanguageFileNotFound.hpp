#ifndef FILENOTFOUNDEXCEPTION_H
#define FILENOTFOUNDEXCEPTION_H

#include <exception>
#include <filesystem>

class LanguageFileNotFound :
    public std::exception
{
public:
    explicit LanguageFileNotFound(const std::experimental::filesystem::path& path);
    char const* what() const override;
private:
    std::string message_;
};

#endif