#include "../include/Station.hpp"
#include "../include/Utilities.hpp"

Station::Station(const std::string& name, const std::string& ip, bool favorite, bool user_defined)
	: name_(name)
	, ip_(ip)
	, favorite_(favorite)
	, user_defined_(user_defined)
{
}

bool Station::operator==(const Station& rhs) const
{
	if (name_ == rhs.name_ && ip_ == rhs.ip_)
		return true;
	return false;
}

nana::listbox::oresolver& operator<<(nana::listbox::oresolver& ores, const Station& station)
{
    return ores << station.name_ << station.ip_ << bool_to_str(station.favorite_) << bool_to_str(station.user_defined_);
}

nana::listbox::iresolver& operator>>(nana::listbox::iresolver& ires, Station& station)
{
    std::string favorite = bool_to_str(station.favorite_);
    std::string user_defined = bool_to_str(station.user_defined_);
    ires >> station.name_;
    ires >> station.ip_;
    ires >> favorite;
    ires >> user_defined;
    return ires;
}
