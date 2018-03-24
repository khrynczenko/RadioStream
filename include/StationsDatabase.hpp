#ifndef STATIONSDATABASE_HPP
#define STATIONSDATABASE_HPP

#include "Station.hpp"
#include "observers/Subject.hpp"
#include <Poco/Data/Session.h>


class StationsDatabase : public Subject
{
public:
    explicit StationsDatabase(const std::string& database_name);
    const std::vector<Station>& get_stations() const noexcept;
    void add_station(const Station& station);
    void remove_station(const Station& station);
    void change_station_favorite_status(const Station& station);
    std::vector<std::string> get_stations_names_with_substring(const std::string& substring) const;
    std::string get_station_ip(const std::string& station_name) const;
private:
    Poco::Data::Session database_;
    std::vector<Station> cached_stations_;
};

#endif
