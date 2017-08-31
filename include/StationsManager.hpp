#ifndef STATIONSMANAGER_HPP
#define STATIONSMANAGER_HPP

#include "Station.hpp"
#include "Constants.hpp"
#include <vector>

/**
 * \brief StationsManager holds up all the data associated with saved stations and helps working with it.
 */
class StationsManager
{
public:
	StationsManager();
	~StationsManager();
    void add_station(const Station& station);
    void delete_station(const Station& station);
	const std::vector<Station>& get_stations() const;
	std::string get_station_ip(const std::string& station_name) const;
	std::string get_station_name(const std::string& ip) const;
	std::vector<std::string> get_matching_stations(const std::string& str) const;
	void set_favorite(std::string station_name);
	void save_all_changes_to_file() const;
private:
	void load_stations(const std::string& filename = constants::STATIONS_FILE);
	std::vector<Station> stations_;
};

#endif
