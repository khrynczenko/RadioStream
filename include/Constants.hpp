#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "Language.hpp"
#include "TextLocalizer.hpp"
#pragma warning(push, 0)
#include <nana/gui/detail/color_schemes.hpp>
#pragma warning(pop)
#include <chrono>
#include <map>

using LanguageNativeName = std::string;

namespace constants {
extern const std::map<const LanguageCode, const LanguageNativeName, LanguageCodeComparator>
    LANGUAGES_CODES_AND_NATIVE_NAMES;

inline const nana::color VERNIER_COLOR{50, 50, 50, 0.5};
inline constexpr std::string_view STATIONS_DATABASE_FILE = "stations.db";
inline constexpr std::string_view CONFIG_FILE = "config.json";
#ifdef _WIN32
inline constexpr std::string_view ICON_PATH = "icon.ico";
#endif
#ifdef unix
inline constexpr std::string_view ICON_PATH = "/usr/local/radiostream/icon.png";
#endif

}  // namespace constants

#endif
