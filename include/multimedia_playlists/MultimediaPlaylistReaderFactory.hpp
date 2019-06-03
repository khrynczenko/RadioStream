#ifndef MULTIMEDIAPLAYLISTREADERFACTORY_HPP
#define MULTIMEDIAPLAYLISTREADERFACTORY_HPP

#include "MultimediaPlaylistReader.hpp"
#include <Poco/URI.h>
#include <memory>

class MultimediaPlaylistReaderFactory
{
public:
    static std::unique_ptr<MultimediaPlaylistReader> make_reader(const Poco::URI& uri);
};

#endif