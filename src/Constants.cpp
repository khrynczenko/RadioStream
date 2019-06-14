#include "../include/Constants.hpp"

namespace constants
{

    using namespace std::string_literals;
    const std::map<const LanguageCode, const LanguageNativeName, LanguageCodeComparator> LANGUAGES_CODES_AND_NATIVE_NAMES =
    {
        std::make_pair(LanguageCode("en"s), "English"s),
        std::make_pair(LanguageCode("pl"s), "Polski"s)
    };
}

