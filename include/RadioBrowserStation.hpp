#ifndef RADIOBROWSERSTATION_HPP
#define RADIOBROWSERSTATION_HPP

#include <nana/gui/widgets/listbox.hpp>
#include <string>

struct RadioBrowserStation
{
    RadioBrowserStation(std::string name, std::string url, std::string country, std::string language);
    std::string name_;
    std::string url_;
    std::string country_;
    std::string language_;
};


nana::listbox::oresolver& operator<<(nana::listbox::oresolver& ores, const RadioBrowserStation& station);
nana::listbox::iresolver& operator>>(nana::listbox::iresolver& ires, RadioBrowserStation& station);
#endif