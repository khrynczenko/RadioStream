#ifndef NOTSUPPORTEDLANGUAGEEXCEPTION_H
#define NOTSUPPORTEDLANGUAGEEXCEPTION_H

#include <exception>
#include <string>
#include "../Language.hpp"

class NotSupportedLanguageException : public std::exception {
   public:
    NotSupportedLanguageException(const LanguageCode& language);
    [[nodiscard]] char const* what() const noexcept override;

   private:
    std::string message_;
};

#endif
