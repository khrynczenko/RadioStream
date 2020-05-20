#ifndef POCOHTTPDOWNLOADER_HPP
#define POCOHTTPDOWNLOADER_HPP

#include "HTTPDownloader.hpp"

class PocoHTTPDownloader : public HTTPDownloader {
   public:
    explicit PocoHTTPDownloader();
    [[nodiscard]] std::string download(std::string_view url) const override;
};

#endif
