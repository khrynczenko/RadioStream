#include "../include/Station.hpp"
#include "../include/Utilities.hpp"

Station::Station(const std::string& name, const std::string& ip, bool favorite, constants::StationTable table)
	: name_(name)
	, ip_(ip)
	, favorite_(favorite)
	, table_(table)
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
    return ores << station.name_ << station.ip_ << bool_to_str(station.favorite_) << std::to_string(static_cast<unsigned short int>(station.table_));
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
    station.table_ = static_cast<constants::StationTable>(std::stoi(table));
    return ires;
}
