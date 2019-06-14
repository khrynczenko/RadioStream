#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "Language.hpp"
#include "TextLocalizer.hpp"
#include <nana/gui/detail/color_schemes.hpp>
#include <chrono>
#include <map>


using LanguageNativeName = std::string;

namespace constants {
    extern const std::map<const LanguageCode, const LanguageNativeName, LanguageCodeComparator> LANGUAGES_CODES_AND_NATIVE_NAMES;


    inline const nana::color VERNIER_COLOR{50, 50, 50, 0.5};
    inline constexpr const char* const STATIONS_DATABASE_FILE = "stations.db";
    inline constexpr const char* const CONFIG_FILE = "config.json";

}

#endif
