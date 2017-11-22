#ifndef STATIONSDATABASE_HPP
#define STATIONSDATABASE_HPP

#include <sqlite_modern_cpp.h>
#include "Station.hpp"


class StationsDatabase
{
public:

    explicit StationsDatabase(const std::string& database_name);
    const std::vector<Station>& get_stations() const;
    const std::vector<Station> get_stations(constants::StationTable table) const;
    void add_station(const Station& station, constants::StationTable table);
    void remove_station(const Station& station, constants::StationTable table);
    void change_station_favorite_status(const Station& station, constants::StationTable table);
    std::vector<std::string> get_stations_names_by_substring(const std::string& substring) const;
    std::string get_station_ip(const std::string& station_name) const;
private:
    std::string get_table_name(constants::StationTable table) const;
    sqlite::database database_;
    std::vector<Station> cached_stations_;
};

#endif
