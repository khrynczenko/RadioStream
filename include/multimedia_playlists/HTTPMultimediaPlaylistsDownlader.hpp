#ifndef HTTPMULTIMEDIAPLAYLISTSDOWNLOADER_HPP
#define HTTPMULTIMEDIAPLAYLISTSDOWNLOADER_HPP

#include <ostream>
#include <string>

class HTTPMultimediaPlaylistsDownloader
{
public:
    virtual ~HTTPMultimediaPlaylistsDownloader() = default;
    virtual std::string download(std::string_view url) const = 0;
};

#endif