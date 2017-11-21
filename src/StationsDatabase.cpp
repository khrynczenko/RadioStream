#include "../include/StationsDatabase.hpp"
#include "../include/Station.hpp"
#include "../include/Utilities.hpp"

StationsDatabase::StationsDatabase(const std::string& database_name)
    : database_(database_name)
{
    for (std::size_t i = static_cast<std::size_t>(constants::StationTable::Default); i < static_cast<std::size_t>(constants::StationTable::StationTableCount); ++i)
    {
        const auto table = static_cast<constants::StationTable>(i);
        database_ << "select * from " + get_table_name(table)
            >> [this, table](int id, std::string name, std::string ip, int favorite)
        {
            cached_stations_.push_back(Station{ name, ip, static_cast<bool>(favorite), table});
        };
    }
}

std::vector<Station> StationsDatabase::get_stations()
{
    return cached_stations_;
}
std::vector<Station> StationsDatabase::get_stations(constants::StationTable table) 
{
    return cached_stations_;
}

void StationsDatabase::add_station(const Station& station, constants::StationTable table)
{
    const auto table_name = get_table_name(table);
    database_ << "insert into " + table_name +  " (name, ip, favorite) values (?, ?, ?)"
        << station.name_
        << station.ip_
        << static_cast<int>(station.favorite_);
    cached_stations_.push_back(station);
}

void StationsDatabase::remove_station(const Station& station, constants::StationTable table)
{
    const auto table_name = get_table_name(table);
    std::cout << station.name_ << ":" << station.ip_;
    database_ << "delete from " + table_name + " where name = ? and ip = ?"
        << station.name_
        << station.ip_;
    cached_stations_.erase(std::find(cached_stations_.begin(), cached_stations_.end(), station));
}

void StationsDatabase::change_station_favorite_status(const Station& station, constants::StationTable table)
{
    const auto table_name = get_table_name(table);
    database_ << "update " + table_name + " set favorite = ? where name = ? and ip = ?"
        << station.favorite_
        << station.name_
        << station.ip_;
    const auto station_found = std::find(cached_stations_.begin(), cached_stations_.end(), station);
    station_found->favorite_ = !station_found->favorite_;
}

std::vector<std::string> StationsDatabase::get_stations_names_by_substring(const std::string& substring) const
{
	std::vector<std::string> matching_station_names;
    const std::string string_to_look_for = string_to_lower(substring);
	for(const auto& station : cached_stations_)
	{
        std::string lower_cased_station_name = string_to_lower(station.name_);
		if (lower_cased_station_name.find(string_to_look_for) != std::string::npos)
		{
            matching_station_names.push_back(lower_cased_station_name);
		}
	}
	return matching_station_names;
}

std::string StationsDatabase::get_station_ip(const std::string& station_name) const
{
    const auto iterator = std::find_if(cached_stations_.cbegin(), cached_stations_.cend(), [&](const Station& station)
    {
        if (station.name_ == station_name)
            return true;
        return false;
    });
    if(iterator == cached_stations_.cend())
    {
        throw;
    }
    return iterator->ip_;
}

std::string StationsDatabase::get_table_name(constants::StationTable table) const
{
    switch(table)
    {
    case constants::StationTable::UserDefined: return "user_defined_stations";
    case constants::StationTable::Default: return "default_stations";
    default: throw;
    }
}
