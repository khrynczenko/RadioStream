#include "../include/Language.hpp"
#include "../include/exceptions/WrongLanguageCodeFormatException.hpp"

LanguageCode::LanguageCode(std::string_view code)
    : code_(code)
{
    if(code_.length() != 2)
    {
        throw WrongLanguageCodeFormatException(code);
    }
}

bool LanguageCode::operator==(const LanguageCode &rhs) const {
    return code_ == rhs.code_;
}

std::string LanguageCode::get_string() const {
    return code_;
}
