#ifndef STATIONSMANAGER_HPP
#define STATIONSMANAGER_HPP

#include "Station.hpp"
#include <vector>

class StationsManager
{
public:
	StationsManager();
	const std::vector<Station>& get_default_stations() const;
	std::string get_station_ip(const std::string& station_name) const;
	std::string get_station_name(const std::string& ip) const;
	std::vector<std::string> search_matching_stations(const std::string& str) const;
private:
	void load_default_stations();
	void load_user_stations();
	std::vector<Station> default_stations_;
	std::vector<Station> user_stations_;
};

#endif
