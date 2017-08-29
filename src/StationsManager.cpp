#include "../include/StationsManager.hpp"
#include "../include/Station.hpp"
#include "../include/Constants.hpp"
#include "../include/Utilities.hpp"
#include <json.hpp>
#include <fstream>
#include <stdexcept>

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
		stations_.push_back(Station(j["name"].get<std::string>(), j["ip"].get<std::string>(), j["favorite"].get<bool>(), j["user_defined"].get<bool>()));
	}
	input.close();
}

std::vector<std::string> StationsManager::get_matching_stations(const std::string& str) const
{
	std::vector<std::string> matching_station_names;
    std::string string_to_look_for = string_to_lower(str);
	for(const auto& station : stations_)
	{
        std::string lower_cased_station_name = string_to_lower(station.name_);
		if (lower_cased_station_name.find(string_to_look_for) != std::string::npos)
		{
            matching_station_names.push_back(lower_cased_station_name);
		}
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
        throw std::runtime_error("Cannot delete station that does not exist.");
    }

}
