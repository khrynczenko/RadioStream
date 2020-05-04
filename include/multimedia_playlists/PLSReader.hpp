#ifndef PLSTOURLREADER_HPP
#define PLSTOURLREADER_HPP

#include "MultimediaPlaylistReader.hpp"

class PLSReader : public MultimediaPlaylistReader {
   public:
    std::string get_station_url(std::istream& input) const override;
};

#endif