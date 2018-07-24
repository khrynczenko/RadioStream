#include "../include/StationsDatabase.hpp"
#include "../include/Station.hpp"
#include "../include/Utilities.hpp"

StationsDatabase::StationsDatabase(std::string_view database_name)
    : database_("SQLite", static_cast<std::string>(database_name))
    , cached_stations_({})
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
    insert << "INSERT INTO stations (name, url, country, language, codec, bitrate, tags) VALUES (?, ?, ?, ?, ?, ?, ?)",
        Poco::Data::Keywords::bind(station.name_),
        Poco::Data::Keywords::bind(station.url_),
        Poco::Data::Keywords::bind(station.country_),
        Poco::Data::Keywords::bind(station.language_),
        Poco::Data::Keywords::bind(station.codec_),
        Poco::Data::Keywords::bind(station.bitrate_),
        Poco::Data::Keywords::bind(station.tags_);
    insert.execute();
    cached_stations_.push_back(station);
    notify(Observer::placeholder, radiostream::Event::StationAddedToDatabase);
}

void StationsDatabase::remove_station(const Station& station)
{
    Poco::Data::Statement delete_statement(database_);
    delete_statement << "DELETE FROM stations WHERE name = ? and url = ?",
        Poco::Data::Keywords::bind(station.name_),
        Poco::Data::Keywords::bind(station.url_);
    delete_statement.execute();
    cached_stations_.erase(std::find(cached_stations_.begin(), cached_stations_.end(), station));
    notify(Observer::placeholder, radiostream::Event::StationDeletedFromDatabase);
}

std::vector<Station> StationsDatabase::get_stations_by_substring(const std::string& substring) const
{
    std::vector<Station> matching_stations;
    const auto string_to_look_for = string_to_lower(substring);
	for(const auto& station : cached_stations_)
	{
        std::string lower_cased_station_name = string_to_lower(station.name_);
		if (lower_cased_station_name.find(string_to_look_for) != std::string::npos)
		{
            matching_stations.push_back(station);
		}
	}
	return matching_stations;
}

void StationsDatabase::create_empty_table_if_does_not_exist()
{
    Poco::Data::Statement create(database_);
    create << "CREATE TABLE IF NOT EXISTS `stations` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `name` TEXT,"
              " `url` TEXT, `country` TEXT, `language` TEXT, `codec` TEXT, `bitrate` TEXT, `tags` TEXT)";
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
        Poco::Data::Keywords::into(station.url_),
        Poco::Data::Keywords::into(station.country_),
        Poco::Data::Keywords::into(station.language_),
        Poco::Data::Keywords::into(station.codec_),
        Poco::Data::Keywords::into(station.bitrate_),
        Poco::Data::Keywords::into(station.tags_),
        Poco::Data::Keywords::range(0, 1);

    while(!select.done())
    {
        select.execute();
        if(select.rowsExtracted() > 0)
        {
            cached_stations_.push_back(station);
        }
    }
}

