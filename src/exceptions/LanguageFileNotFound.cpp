#include "../../include/exceptions/LanguageFileNotFound.hpp"

LanguageFileNotFound::LanguageFileNotFound(const std::experimental::filesystem::path& path)
    : std::exception()
{
    message_ = "Language file at " + path.string() + " not found.";
}

char const* LanguageFileNotFound::what() const
{
    return message_.c_str();
}
