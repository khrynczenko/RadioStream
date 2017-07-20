#include "../include/StationsManager.hpp"
#include <fstream>
#include <json.hpp>
#include <vector>
#include "../include/Station.hpp"
#include "../include/Constants.hpp"
#include "../include/Utilities.hpp"

using json = nlohmann::json;

StationsManager::StationsManager()
{
	load_stations();
}

StationsManager::~StationsManager()
{
	save_all_changes_to_file();
}

const std::vector<Station>& StationsManager::get_stations() const
{
	return stations_;
}

std::string StationsManager::get_station_ip(const std::string& station_name) const
{
		auto iterator = std::find_if(stations_.cbegin(),stations_.cend(),[&station_name](const Station& station)
		{
			if (station.name_ == station_name)
				return true;
			return false;
		});
		if (iterator != stations_.cend())
			return iterator->ip_;
		throw;
}

std::string StationsManager::get_station_name(const std::string& ip) const
{
	auto iterator = std::find_if(stations_.cbegin(), stations_.cend(), [&ip](const Station& station)
	{
		if (station.ip_ == ip)
			return true;
		return false;
	});
	if (iterator != stations_.cend())
		return iterator->ip_;
	throw;
}


void StationsManager::load_stations(const std::string& filename)
{
	std::ifstream input{ filename };
	std::string temp{ "" };
	while (std::getline(input, temp))
	{
		json j = json::parse(temp);
		stations_.push_back(Station(j["name"].get<std::string>(), j["ip"].get<std::string>(),j["favorite"].get<bool>(), j["user_defined"].get<bool>()));
	}
	input.close();
}

std::vector<std::string> StationsManager::search_matching_stations(const std::string& str) const
{
	std::vector<std::string> matching_station_names;
	std::string searched_str;
	std::transform(str.cbegin(), str.cend(), std::back_inserter(searched_str), easytolower);
	for(const auto& station : stations_)
	{
		std::string lower_cased;
		std::transform(station.name_.cbegin(), station.name_.cend(), std::back_inserter(lower_cased), easytolower);
		if (lower_cased.find(searched_str) != std::string::npos)
			matching_station_names.push_back(station.name_);
	}
	return matching_station_names;
}

void StationsManager::set_favorite(std::string station_name)
{
	auto iterator = std::find_if(stations_.begin(), stations_.end(), [&station_name](const Station& station)
	{
		if (station.name_ == station_name)
			return true;
		return false;
	});
	if (iterator != stations_.end()) 
	{
		iterator->favorite_ = !iterator->favorite_;
		return;
	}
	throw;
}

void StationsManager::save_all_changes_to_file() const
{
	std::ofstream output{ constants::STATIONS_FILE };
	json j;
	for(auto station : stations_)
	{
		j["ip"] = station.ip_;
		j["name"] = station.name_;
		j["favorite"] = station.favorite_;
		j["user_defined"] = station.user_defined_;
		output << j.dump(-1) << '\n';
	}
	output.close();
}

void StationsManager::add_station(const Station& station)
{
    stations_.push_back(station);
}

void StationsManager::delete_station(const Station& station)
{
    auto it = std::find(stations_.begin(), stations_.end(), station);
    if (it != stations_.end())
    {
        stations_.erase(it);
    }
    else
    {
        throw std::exception("Could not delete station that does not exist.");
    }

}
