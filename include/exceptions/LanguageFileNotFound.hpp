#ifndef FILENOTFOUNDEXCEPTION_H
#define FILENOTFOUNDEXCEPTION_H

#include <exception>
#include <experimental/filesystem>

class LanguageFileNotFound :
    public std::exception
{
public:
    explicit LanguageFileNotFound(const std::experimental::filesystem::path& path);
    char const* what() const noexcept override;
private:
    std::string message_;
};

#endif
