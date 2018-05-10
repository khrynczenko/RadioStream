#ifndef POCOHTTPDOWNLOADER_HPP
#define POCOHTTPDOWNLOADER_HPP

#include "HTTPMultimediaPlaylistsDownlader.hpp"

class PocoHTTPDownloader : public HTTPMultimediaPlaylistsDownloader
{
public:
   std::string download(std::string_view url) const override;
};

#endif
