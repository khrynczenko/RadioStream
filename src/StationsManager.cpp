#include "../include/StationsManager.hpp"
#include <fstream>
#include <json.hpp>
#include <vector>
using json = nlohmann::json;

StationsManager::StationsManager()
{
	load_default_stations();
	load_user_stations();
}

const std::vector<Station>& StationsManager::get_default_stations() const
{
	return default_stations;
}

std::string StationsManager::get_station_ip(const std::string& station_name) const
{
		auto iterator = std::find_if(default_stations.cbegin(),default_stations.cend(),[&station_name](const Station& station)
		{
			if (station.name == station_name)
				return true;
			return false;
		});
		if (iterator != default_stations.cend())
			return iterator->ip;
		iterator = std::find_if(user_stations.cbegin(), user_stations.cend(), [&station_name](const Station& station)
		{
			if (station.name == station_name)
				return true;
			return false;
		});
		if (iterator != user_stations.cend())
			return iterator->ip;
		throw;
}

std::string StationsManager::get_station_name(const std::string& ip) const
{
	auto iterator = std::find_if(default_stations.cbegin(), default_stations.cend(), [&ip](const Station& station)
	{
		if (station.ip == ip)
			return true;
		return false;
	});
	if (iterator != default_stations.cend())
		return iterator->ip;
	iterator = std::find_if(user_stations.cbegin(), user_stations.cend(), [&ip](const Station& station)
	{
		if (station.ip == ip)
			return true;
		return false;
	});
	if (iterator != user_stations.cend())
		return iterator->name;
	throw;
}


void StationsManager::load_default_stations()
{
	
	std::ifstream input{ "default_stations.data" };
	std::string temp{ "" };
	while (std::getline(input, temp))
	{
		json j = json::parse(temp);
		default_stations.push_back(Station(j["name"].get<std::string>(), j["ip"].get<std::string>()));
	}
	input.close();
}

void StationsManager::load_user_stations()
{
}

std::vector<std::string> StationsManager::search_matching_stations(const std::string& str) const
{
	std::vector<std::string> matching_station_names;
	for(const auto& station : default_stations)
	{
		std::string lower_cased;
		std::transform(station.name.cbegin(), station.name.cend(), std::back_inserter(lower_cased), tolower);
		if (lower_cased.find(str) != std::string::npos)
			matching_station_names.push_back(station.name);
	}
	return matching_station_names;
}
