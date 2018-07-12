#include "../include/Station.hpp"
#include "../include/Utilities.hpp"

Station::Station(std::string_view name, std::string_view ip)
	: name_(name)
	, ip_(ip)
{
}

Station::Station(const RadioBrowserStation& rhs)
    : name_(rhs.name_)
    , ip_(rhs.url_)
{
}

bool Station::operator==(const Station& rhs) const noexcept
{
    return (name_ == rhs.name_) && (ip_ == rhs.ip_);
}

nana::listbox::oresolver& operator<<(nana::listbox::oresolver& ores, const Station& station)
{
    return ores << station.name_ << station.ip_;
}

nana::listbox::iresolver& operator>>(nana::listbox::iresolver& ires, Station& station)
{
    ires >> station.name_;
    ires >> station.ip_;
    return ires;
}
