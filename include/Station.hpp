#ifndef STATION_HPP
#define STATION_HPP

#include <string>

struct Station
{
	Station(const std::string& name_, const std::string& ip_);
	~Station() = default;
	const std::string name_;
	const std::string ip_;
};

#endif