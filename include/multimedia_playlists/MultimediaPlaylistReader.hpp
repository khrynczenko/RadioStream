#ifndef MULTIMEDIAPLAYLISTREADER_HPP
#define MULTIMEDIAPLAYLISTREADER_HPP

#include <istream>
#include <string>

class MultimediaPlaylistReader {
   public:
    virtual ~MultimediaPlaylistReader() = default;
    virtual std::string get_station_url(std::istream& input) const = 0;
};

#endif