#ifndef M3UTOURLCONVERTER_HPP
#define M3UTOURLCONVERTER_HPP

#include "MultimediaPlaylistReader.hpp"

class M3UReader : public MultimediaPlaylistReader {
   public:
    std::string get_station_url(std::istream& input) const override;
};

#endif
