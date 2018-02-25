#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <nana/gui/detail/color_schemes.hpp>
#include <chrono>

namespace constants
{
	enum class StationListboxCategories
	{
		NanaDefault,
	};

	enum class StationListboxColumns
	{
		Name,
        Ip,
		Favorite,
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
    inline const char* STATIONS_DATABASE_FILE = "stations.db";
    inline const char* CONFIG_FILE_PATH = "config.json";

}

#endif
