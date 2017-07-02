#ifndef STATION_HPP
#define STATION_HPP

#include <string>

struct Station
{
	Station(const std::string& name_, const std::string& ip_, bool favorite, bool user_defined);
	Station(const Station&);
	Station& operator=(const Station&);
	~Station() = default;
	bool operator==(const Station& rhs) const;
	const std::string name_;
	const std::string ip_;
	bool favorite_;
	bool user_defined_;
};

#endif