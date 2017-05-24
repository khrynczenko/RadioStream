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
	return default_stations_;
}

std::string StationsManager::get_station_ip(const std::string& station_name) const
{
		auto iterator = std::find_if(default_stations_.cbegin(),default_stations_.cend(),[&station_name](const Station& station)
		{
			if (station.name_ == station_name)
				return true;
			return false;
		});
		if (iterator != default_stations_.cend())
			return iterator->ip_;
		iterator = std::find_if(user_stations_.cbegin(), user_stations_.cend(), [&station_name](const Station& station)
		{
			if (station.name_ == station_name)
				return true;
			return false;
		});
		if (iterator != user_stations_.cend())
			return iterator->ip_;
		throw;
}

std::string StationsManager::get_station_name(const std::string& ip) const
{
	auto iterator = std::find_if(default_stations_.cbegin(), default_stations_.cend(), [&ip](const Station& station)
	{
		if (station.ip_ == ip)
			return true;
		return false;
	});
	if (iterator != default_stations_.cend())
		return iterator->ip_;
	iterator = std::find_if(user_stations_.cbegin(), user_stations_.cend(), [&ip](const Station& station)
	{
		if (station.ip_ == ip)
			return true;
		return false;
	});
	if (iterator != user_stations_.cend())
		return iterator->name_;
	throw;
}


void StationsManager::load_default_stations()
{
	
	std::ifstream input{ "default_stations.data" };
	std::string temp{ "" };
	while (std::getline(input, temp))
	{
		json j = json::parse(temp);
		default_stations_.push_back(Station(j["name"].get<std::string>(), j["ip"].get<std::string>()));
	}
	input.close();
}

void StationsManager::load_user_stations()
{
}

std::vector<std::string> StationsManager::search_matching_stations(const std::string& str) const
{
	std::vector<std::string> matching_station_names;
	std::string searched_str;
	std::transform(str.cbegin(), str.cend(), std::back_inserter(searched_str), tolower);
	for(const auto& station : default_stations_)
	{
		std::string lower_cased;
		std::transform(station.name_.cbegin(), station.name_.cend(), std::back_inserter(lower_cased), tolower);
		if (lower_cased.find(searched_str) != std::string::npos)
			matching_station_names.push_back(station.name_);
	}
	return matching_station_names;
}
