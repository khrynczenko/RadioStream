#ifndef MULTIMEDIAPLAYLISTREADERFACTORY_HPP
#define MULTIMEDIAPLAYLISTREADERFACTORY_HPP

#include "MultimediaPlaylistReader.hpp"
#pragma warning(push, 0)
#include <Poco/URI.h>
#pragma warning(pop)
#include <memory>

class MultimediaPlaylistReaderFactory {
   public:
    [[nodiscard]] static std::unique_ptr<MultimediaPlaylistReader> make_reader(
        const Poco::URI& uri);
};

#endif