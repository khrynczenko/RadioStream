#include "../include/Station.hpp"
#include "../include/Utilities.hpp"

Station::Station(const std::string& name, const std::string& ip, bool favorite)
	: name_(name)
	, ip_(ip)
	, favorite_(favorite)
{
}

bool Station::operator==(const Station& rhs) const
{
    if (name_ == rhs.name_ && ip_ == rhs.ip_)
    {
		return true;
    }
	return false;
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
