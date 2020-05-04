#ifndef HTTPMULTIMEDIAPLAYLISTSDOWNLOADER_HPP
#define HTTPMULTIMEDIAPLAYLISTSDOWNLOADER_HPP

#include <ostream>
#include <string>

class HTTPDownloader {
   public:
    virtual ~HTTPDownloader() = default;
    virtual std::string download(std::string_view url) const = 0;
};

#endif