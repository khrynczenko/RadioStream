#include "../include/Language.hpp"
#include "../include/exceptions/WrongLanguageCodeFormatException.hpp"

LanguageCode::LanguageCode(std::string_view code)
    : std::string()
{
    if(code.length() != 2)
    {
        throw WrongLanguageCodeFormatException(code);
    }
    resize(2u);
    insert(0, code);
}
