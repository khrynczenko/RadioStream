#ifndef STATION_HPP
#define STATION_HPP

#include "RadioBrowserStation.hpp"
#include <nana/gui/widgets/listbox.hpp>

struct Station
{
	Station(std::string_view name, std::string_view ip);
    explicit Station(const RadioBrowserStation& rhs);
    Station() = default;
	bool operator==(const Station& rhs) const noexcept;
	std::string name_;
	std::string ip_;
};

nana::listbox::oresolver& operator<<(nana::listbox::oresolver& ores, const Station& station);
nana::listbox::iresolver& operator>>(nana::listbox::iresolver& ires, Station& station);
#endif