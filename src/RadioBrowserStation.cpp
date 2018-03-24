#include "../include/RadioBrowserStation.hpp"

RadioBrowserStation::RadioBrowserStation(std::string_view name, std::string_view url, std::string_view country,
                                         std::string_view language, std::string_view codec, std::string_view tags)
    : name_(name)
    , url_(url)
    , country_(country)
    , language_(language)
    , codec_(codec)
    , tags_(tags)
{
}

nana::listbox::oresolver& operator<<(nana::listbox::oresolver& ores, const RadioBrowserStation& station)
{
    return ores << station.name_ << station.url_ << station.country_ << station.language_ << station.codec_ << station.tags_;
}

nana::listbox::iresolver& operator>>(nana::listbox::iresolver& ires, RadioBrowserStation& station)
{
    return ires >> station.name_ >> station.url_ >> station.country_ >> station.language_ >> station.codec_ >> station.tags_;
}
