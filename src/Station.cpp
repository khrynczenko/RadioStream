#include "../include/Station.hpp"
#include "../include/Utilities.hpp"

Station::Station(std::string_view name, std::string_view ip, bool favorite)
	: name_(name)
	, ip_(ip)
	, favorite_(favorite)
{
}

Station::Station(const RadioBrowserStation& rhs)
    : name_(rhs.name_)
    , ip_(rhs.url_)
    , favorite_(false)
{
}

bool Station::operator==(const Station& rhs) const noexcept
{
    return (name_ == rhs.name_) && (ip_ == rhs.ip_);
}

nana::listbox::oresolver& operator<<(nana::listbox::oresolver& ores, const Station& station)
{
    return ores << station.name_ << station.ip_ << bool_to_str(station.favorite_);
}

nana::listbox::iresolver& operator>>(nana::listbox::iresolver& ires, Station& station)
{
    std::string favorite;
    std::string table;
    ires >> station.name_;
    ires >> station.ip_;
    ires >> favorite;
    ires >> table;
    station.favorite_ = str_to_bool(favorite);
    return ires;
}
