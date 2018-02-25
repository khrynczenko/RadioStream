#ifndef RADIOBROWSERSTATION_HPP
#define RADIOBROWSERSTATION_HPP

#include <nana/gui/widgets/listbox.hpp>
#include <string>

struct RadioBrowserStation
{
    RadioBrowserStation(std::string_view name, std::string_view url, std::string_view country,
                        std::string_view language, std::string_view codec, std::string_view tags);
    std::string name_;
    std::string url_;
    std::string country_;
    std::string language_;
    std::string codec_;
    std::string tags_;
};


nana::listbox::oresolver& operator<<(nana::listbox::oresolver& ores, const RadioBrowserStation& station);
nana::listbox::iresolver& operator>>(nana::listbox::iresolver& ires, RadioBrowserStation& station);
#endif