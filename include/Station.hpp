#ifndef STATION_HPP
#define STATION_HPP

#include <nana/gui/widgets/listbox.hpp>

struct Station
{
	Station(const std::string& name_, const std::string& ip_, bool favorite, bool user_defined);
    Station() = default;
	bool operator==(const Station& rhs) const;
	std::string name_;
	std::string ip_;
	bool favorite_;
	bool user_defined_;
};

nana::listbox::oresolver& operator<<(nana::listbox::oresolver& ores, const Station& station);
nana::listbox::iresolver& operator>>(nana::listbox::iresolver& ires, Station& station);
#endif