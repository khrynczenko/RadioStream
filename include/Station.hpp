#ifndef STATION_HPP
#define STATION_HPP

#include <nana/gui/widgets/listbox.hpp>

struct Station
{
    Station() = default;
    Station(std::string_view name, std::string_view url, std::string_view country,
                        std::string_view language, std::string_view codec, std::string_view bitrate, std::string_view tags);
    bool operator==(const Station& rhs) const noexcept;
    std::string name_;
    std::string url_;
    std::string country_;
    std::string language_;
    std::string codec_;
    std::string bitrate_;
    std::string tags_;
};

nana::listbox::oresolver& operator<<(nana::listbox::oresolver& ores, const Station& station);
nana::listbox::iresolver& operator>>(nana::listbox::iresolver& ires, Station& station);
#endif