#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <nana/gui/detail/color_schemes.hpp>

namespace constants
{
	enum class StationListboxCategories
	{
		NanaDefault,
		UserDefined,
		Default
		
	};
	enum class StationListboxColumns
	{
		Name,
		Favorite,
		UserDefined
	};

	const nana::color VERNIER_COLOR{ 50,50,50,0.5 };

	constexpr const char* STATIONS_FILE = "stations.data";
	constexpr const char* DEFAULT_STATIONS_FILE = "default_stations.data";

}

#endif