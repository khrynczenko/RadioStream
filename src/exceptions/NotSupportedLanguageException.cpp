#include "../../include/exceptions/NotSupportedLanguageException.hpp"

NotSupportedLanguageException::NotSupportedLanguageException(const LanguageCode& language)
    : std::exception(), message_() {
    message_ = "Language \"" + language.as_string() + "\" is not supported.";
}

char const* NotSupportedLanguageException::what() const noexcept { return message_.c_str(); }
