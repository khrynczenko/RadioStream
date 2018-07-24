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

bool LanguageCode::operator==(const LanguageCode &rhs) const noexcept {
    return code_ == rhs.code_;
}

std::string LanguageCode::as_string() const {
    return code_;
}

bool LanguageCodeComparator::operator()(const LanguageCode& lhs, const LanguageCode& rhs) const noexcept
{
    return lhs.as_string() < rhs.as_string();
}
