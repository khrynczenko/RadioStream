#include "../../include/exceptions/NotSupportedLanguageException.hpp""

NotSupportedLanguageException::NotSupportedLanguageException(const std::string& language)
    : std::exception()
    , message_()
{
    message_ = "Language \"" + language + "\" is not supported.";
}

char const* NotSupportedLanguageException::what() const
{
    return message_.c_str();
}
