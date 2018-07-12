#include "../include/StationsDatabase.hpp"
#include "../include/Station.hpp"
#include "../include/Utilities.hpp"

StationsDatabase::StationsDatabase(std::string_view database_name)
    : database_("SQLite", static_cast<std::string>(database_name))
{
    create_empty_table_if_does_not_exist();
    cache_stations_stored_in_database();
}

const std::vector<Station>& StationsDatabase::get_stations() const noexcept
{
    return cached_stations_;
}

void StationsDatabase::add_station(const Station& station)
{
    Poco::Data::Statement insert(database_);
    insert << "INSERT INTO stations (name, ip) VALUES(?, ?)",
        Poco::Data::Keywords::bind(station.name_),
        Poco::Data::Keywords::bind(station.ip_);
    insert.execute();
    cached_stations_.push_back(station);
    notify(Observer::placeholder, radiostream::Event::StationAddedToDatabase);
}

void StationsDatabase::remove_station(const Station& station)
{
    Poco::Data::Statement delete_statement(database_);
    delete_statement << "DELETE FROM stations WHERE name = ? and ip = ?",
        Poco::Data::Keywords::bind(station.name_),
        Poco::Data::Keywords::bind(station.ip_);
    delete_statement.execute();
    cached_stations_.erase(std::find(cached_stations_.begin(), cached_stations_.end(), station));
    notify(Observer::placeholder, radiostream::Event::StationDeletedFromDatabase);
}

std::vector<std::string> StationsDatabase::get_stations_names_with_substring(const std::string& substring) const
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

void StationsDatabase::create_empty_table_if_does_not_exist()
{
    Poco::Data::Statement create(database_);
    create << "CREATE TABLE IF NOT EXISTS `stations` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `name` TEXT, `ip` TEXT )";
    create.execute();
}

void StationsDatabase::cache_stations_stored_in_database()
{
    Poco::Data::Statement select(database_);
    Station station;
    int id;
    select << "SELECT * FROM stations",
        Poco::Data::Keywords::into(id),
        Poco::Data::Keywords::into(station.name_),
        Poco::Data::Keywords::into(station.ip_),
        Poco::Data::Keywords::range(0, 1);

    while(!select.done())
    {
        select.execute();
        cached_stations_.push_back(station);
    }
}

