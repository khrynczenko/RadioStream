#include "../include/RadioBrowserStation.hpp"

RadioBrowserStation::RadioBrowserStation(std::string name, std::string url, std::string country,
    std::string language)
    : name_(std::move(name))
    , url_(std::move(url))
    , country_(std::move(country))
    , language_(std::move(language))
{
}

nana::listbox::oresolver& operator<<(nana::listbox::oresolver& ores, const RadioBrowserStation& station)
{
    return ores << station.name_ << station.url_ << station.country_ << station.language_;
}

nana::listbox::iresolver& operator>>(nana::listbox::iresolver& ires, RadioBrowserStation& station)
{
    return ires >> station.name_ >> station.url_ >> station.country_ >> station.language_;
}
