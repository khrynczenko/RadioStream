#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "Language.hpp"
#include "TextLocalizer.hpp"
#include <nana/gui/detail/color_schemes.hpp>
#include <chrono>
#include <map>


using LanguageNativeName = std::string; 

namespace constants
{
    extern const std::map<const LanguageCode, const LanguageNativeName, LanguageCodeComparator> LANGUAGES_CODES_AND_NATIVE_NAMES;

	enum class StationListboxCategories
	{
		NanaDefault,
	};

	enum class StationListboxColumns
	{
		Name,
        Ip,
	};

    enum class SearchListboxColumns
    {
        Name,
        Url,
        Country,
        Language,
        Codec,
        Tags
    };

    enum class ContextualMenus
    {
        StationListbox,
        SongLabel
    };

	const nana::color VERNIER_COLOR{ 50,50,50,0.5 };

    constexpr std::chrono::seconds TIME_TO_CHECK_IF_SONG_CHANGED{ 10 };
    constexpr char* STATIONS_DATABASE_FILE = "stations.db";
    constexpr char* CONFIG_FILE_PATH = "config.json";

}

#endif
